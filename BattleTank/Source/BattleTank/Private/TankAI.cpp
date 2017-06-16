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
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAI::BeginPlay possessing %s"), *ControlledTank->GetName());
	}

	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAI::BeginPlay player tank is %s"), *PlayerTank->GetName());
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
