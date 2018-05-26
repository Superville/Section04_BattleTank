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

	// ...
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
		AimNormal = LaunchVelocity.GetSafeNormal();
		bValidAimLocation = true;

		//test
/*		DrawDebugBox(GetOwner()->GetWorld(), BarrelLoc, FVector(25, 25, 25), FColor(0, 255, 0));
		DrawDebugBox(GetOwner()->GetWorld(), InAimTargetLocation, FVector(25, 25, 25), FColor(255, 0, 0));
		DrawDebugLine(GetOwner()->GetWorld(), BarrelLoc, BarrelLoc + (AimNormal * 500), FColor(0, 255, 0)); */
	}
	else
	{
//		auto Time = GetWorld()->GetTimeSeconds();
//		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), Time);

		AimNormal = (InAimTargetLocation - BarrelLoc).GetSafeNormal();
		bValidAimLocation = false;
	}
}

void UTankAimingComponent::UpdateTurretRotation(float DeltaTime)
{
	if (!ensure(Barrel && Turret)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimNormal.Rotation();
	auto DeltaRotator = (AimAsRotator - BarrelRotator).GetNormalized();
	Turret->Rotate(DeltaRotator.Yaw);
	if (bValidAimLocation) 
	{
		Barrel->Elevate(DeltaRotator.Pitch);
	}
	

//	UE_LOG(LogTemp, Warning, TEXT("%s"), *DeltaRotator.ToString());
	if (!bValidAimLocation)
	{
		FiringStatus = EFiringStatus::Unsolved;
	}
	else if (IsReloading())
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (FMath::Abs(DeltaRotator.Pitch) < 1 && FMath::Abs(DeltaRotator.Yaw) < 1 )
	{
		FiringStatus = EFiringStatus::Locked;
	}
	else
	{
		FiringStatus = EFiringStatus::Aligning;
	}
}


void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }

	auto CurrentTime = GetWorld()->GetTimeSeconds();
	//	UE_LOG(LogTemp, Warning, TEXT("%f: ATank::Fire"), CurrentTime);

	if (IsReadyToFire())
	{

		auto MuzzleLoc = Barrel->GetSocketLocation(FName("Muzzle"));
		auto MuzzleRot = Barrel->GetSocketRotation(FName("Muzzle"));
		FActorSpawnParameters ASP;
		ASP.Instigator = Cast<APawn>(GetOwner());

		auto Proj = GetWorld()->SpawnActor<ATankProjectile>(ProjectileClass, MuzzleLoc, MuzzleRot, ASP);
		Proj->LaunchProjectile(ProjectileSpeed);

		NextFireTime = CurrentTime + (1.f / FireRatePerSecond);

		/*	DrawDebugBox(GetWorld(), MuzzleLoc, FVector(25, 25, 25), FColor(0, 0, 255),true,10.f);

		//test
		if (Proj)
		{
		UE_LOG(LogTemp, Warning, TEXT("%f: Spawned projectile %s"), CurrentTime, *Proj->GetName());
		}
		else
		{
		UE_LOG(LogTemp, Warning, TEXT("%f: No Proj"), CurrentTime);
		}*/
	}
}

bool UTankAimingComponent::IsReloading()
{
	if (GetWorld()->GetTimeSeconds() < NextFireTime)
	{
		return true;
	}
	return false;
}

bool UTankAimingComponent::IsReadyToFire(bool bReqLocked)
{
	if(IsReloading())
	{
		return false;
	}

	if (bReqLocked && FiringStatus != EFiringStatus::Locked)
	{
		return false;
	}

	return true;
}