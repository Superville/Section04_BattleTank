// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankProjectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Tank Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	AimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	AimingComponent->SetTurretReference(TurretToSet);
}

void ATank::AimAt(FVector InAimTargetLocation)
{
	AimingComponent->AimAt(InAimTargetLocation, ProjectileSpeed);
}

bool ATank::IsReadyToFire()
{
	if (GetWorld()->GetTimeSeconds() < NextFireTime)
	{
		return false;
	}

	return true;
}

void ATank::Fire()
{
	auto Time = GetWorld()->GetTimeSeconds();
//	UE_LOG(LogTemp, Warning, TEXT("%f: ATank::Fire"), Time);

	if (Barrel && IsReadyToFire())
	{

		auto MuzzleLoc = Barrel->GetSocketLocation(FName("Muzzle"));
		auto MuzzleRot = Barrel->GetSocketRotation(FName("Muzzle"));
		FActorSpawnParameters ASP;
		ASP.Instigator = this;

		auto Proj = GetWorld()->SpawnActor<ATankProjectile>(ProjectileClass, MuzzleLoc, MuzzleRot, ASP);
		Proj->LaunchProjectile(ProjectileSpeed);

		NextFireTime = GetWorld()->GetTimeSeconds() + (1.f / FireRatePerSecond);

		/*	DrawDebugBox(GetWorld(), MuzzleLoc, FVector(25, 25, 25), FColor(0, 0, 255),true,10.f);

			//test
			if (Proj)
			{
				UE_LOG(LogTemp, Warning, TEXT("%f: Spawned projectile %s"), Time, *Proj->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%f: No Proj"), Time);
			}*/
	}
}