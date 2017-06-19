// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAI.h"


void ATankAI::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ATankAI not possessing a Tank"));
	}
}

ATank* ATankAI::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
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
	
	ATank* CT = GetControlledTank();
	ATank* PT = GetPlayerTank();
	if (CT && PT)
	{
		// Move toward player (PT)

		// Aim toward the player
		CT->AimAt(PT->GetActorLocation());

		// Fire if ready
	}
}
