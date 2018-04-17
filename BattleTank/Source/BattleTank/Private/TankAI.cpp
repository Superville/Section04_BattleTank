// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAI.h"


void ATankAI::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAI::Possess(APawn* P)
{
	Super::Possess(P);

	ControlledTank = Cast<ATank>(GetPawn());
}

ATank* ATankAI::GetPlayerTank() const
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC != nullptr)
	{
		return Cast<ATank>(PC->GetPawn());
	}
	return nullptr;
}

void ATankAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ATank* PT = GetPlayerTank();
	if (ControlledTank && PT)
	{
		// Move toward player (PT)
		MoveToActor(PT, AcceptanceRadius);

		// Aim toward the player
		ControlledTank->AimAt(PT->GetActorLocation());

		// Fire if ready
		if (IsReadyToFire())
		{
			Fire();
		}
	}
}

bool ATankAI::IsReadyToFire()
{
	if (ControlledTank)
	{
		return ControlledTank->IsReadyToFire();
	}
	return false;
}

void ATankAI::Fire()
{
	if (ControlledTank)
	{
		ControlledTank->Fire();
	}
}
