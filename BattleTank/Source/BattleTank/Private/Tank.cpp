// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


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
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateTurretRotation(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATank::AimAt(FVector InAimTargetLocation)
{
	AimTargetLocation = InAimTargetLocation;

	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetName(), *InAimTargetLocation.ToString());
}

void ATank::UpdateTurretRotation(float DeltaTime)
{
	// Rotate Azimuth Component toward AimTarget at AzimuthRotationSpeed (ensure no overshoot)
	
	// Rotate Elevation Component toward AimTarget at ElavationRotationSpeed (ensure no overshoot)

	// If CurrentAimRotation equals TargetAimLocation
		// Set bAimRotationReady true
}