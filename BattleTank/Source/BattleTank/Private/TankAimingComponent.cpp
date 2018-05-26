// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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


void UTankAimingComponent::AimAt(FVector InAimTargetLocation, float ProjSpeed)
{
	if (!ensure(Barrel && Turret)) { return; }

	auto BarrelLoc = Barrel->GetComponentLocation();
	FVector LaunchVelocity;
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		BarrelLoc,
		InAimTargetLocation,
		ProjSpeed,
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
	ATank* Tank = Cast<ATank>(GetOwner());
	if (!ensure(Tank && Barrel && Turret)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimNormal.Rotation();
	auto DeltaRotator = (AimAsRotator - BarrelRotator).GetNormalized();
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

//	UE_LOG(LogTemp, Warning, TEXT("%s"), *DeltaRotator.ToString());
	if (!bValidAimLocation)
	{
		FiringStatus = EFiringStatus::Unsolved;
	}
	else if (Tank != nullptr && !Tank->IsReadyToFire())
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