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
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = FindComponentByClass<UTankAimingComponent>();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATank::AimAt(FVector InAimTargetLocation)
{
	if (!ensure(AimingComponent)) { return; }
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
	if (!ensure(AimingComponent && AimingComponent->Barrel)) { return; }

	auto CurrentTime = GetWorld()->GetTimeSeconds();
//	UE_LOG(LogTemp, Warning, TEXT("%f: ATank::Fire"), CurrentTime);

	if (IsReadyToFire())
	{

		auto MuzzleLoc = AimingComponent->Barrel->GetSocketLocation(FName("Muzzle"));
		auto MuzzleRot = AimingComponent->Barrel->GetSocketRotation(FName("Muzzle"));
		FActorSpawnParameters ASP;
		ASP.Instigator = this;

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