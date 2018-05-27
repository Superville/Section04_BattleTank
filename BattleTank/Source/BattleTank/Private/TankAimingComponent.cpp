// Copyright Steve Superville

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	NextFireTime = GetWorld()->GetTimeSeconds() + (1.f / FireRatePerSecond);
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateTurretRotation(DeltaTime);
	UpdateFiringStatus();
}


void UTankAimingComponent::AimAt(FVector InAimTargetLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	auto BarrelLoc = Barrel->GetComponentLocation();
	FVector LaunchVelocity;
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		BarrelLoc,
		InAimTargetLocation,
		ProjectileSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		bValidAimLocation = true;

		//test
/*		DrawDebugBox(GetOwner()->GetWorld(), BarrelLoc, FVector(25, 25, 25), FColor(0, 255, 0));
		DrawDebugBox(GetOwner()->GetWorld(), InAimTargetLocation, FVector(25, 25, 25), FColor(255, 0, 0));
		DrawDebugLine(GetOwner()->GetWorld(), BarrelLoc, BarrelLoc + (AimDirection * 500), FColor(0, 255, 0)); */
	}
	else
	{
		AimDirection = (InAimTargetLocation - BarrelLoc).GetSafeNormal();
		bValidAimLocation = false;
	}
}

void UTankAimingComponent::UpdateTurretRotation(float DeltaTime)
{
	if (!ensure(Barrel && Turret)) { return; }

	auto BarrelFwd = Barrel->GetForwardVector();
	auto BarrelRotator = BarrelFwd.Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = (AimAsRotator - BarrelRotator).GetNormalized();
	Turret->Rotate(DeltaRotator.Yaw);
	if (bValidAimLocation) 
	{
		Barrel->Elevate(DeltaRotator.Pitch);
	}
	
}

void UTankAimingComponent::Fire()
{
	if (IsReadyToFire())
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileClass)) { return; }

		auto MuzzleLoc = Barrel->GetSocketLocation(FName("Muzzle"));
		auto MuzzleRot = Barrel->GetSocketRotation(FName("Muzzle"));
		
		FActorSpawnParameters ASP;
		ASP.Instigator = Cast<APawn>(GetOwner());

		auto Proj = GetWorld()->SpawnActor<ATankProjectile>(ProjectileClass, MuzzleLoc, MuzzleRot, ASP);
		if (Proj)
		{
			Proj->LaunchProjectile(ProjectileSpeed);
			NextFireTime = GetWorld()->GetTimeSeconds() + (1.f / FireRatePerSecond);
			AmmoCount--;
		}

		//DrawDebugBox(GetWorld(), MuzzleLoc, FVector(25, 25, 25), FColor(0, 0, 255),true,10.f);
	}
}

bool UTankAimingComponent::IsReloading() const
{
	if (GetWorld()->GetTimeSeconds() < NextFireTime)
	{
		return true;
	}
	return false;
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelFwd = Barrel->GetForwardVector();
	return !AimDirection.Equals(BarrelFwd, 0.01);
}

int UTankAimingComponent::GetAmmoLeft() const
{
	return AmmoCount;
}

bool UTankAimingComponent::HasAmmo() const
{
	return (GetAmmoLeft() > 0);
}

bool UTankAimingComponent::IsReadyToFire(bool bReqLocked) const
{
	if (!HasAmmo())
	{
		return false;
	}

	if(IsReloading())
	{
		return false;
	}

	if (bReqLocked && IsBarrelMoving())
	{
		return false;
	}

	return true;
}

void UTankAimingComponent::UpdateFiringStatus()
{
	if (!HasAmmo())
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if (!bValidAimLocation)
	{
		FiringStatus = EFiringStatus::Unsolved;
	}
	else if (IsReloading())
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aligning;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}