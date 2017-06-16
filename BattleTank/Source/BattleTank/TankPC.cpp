// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPC.h"

void ATankPC::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ATankPC not possessing a tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPC::BeginPlay %s"), *ControlledTank->GetName());
	}
}

ATank* ATankPC::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}