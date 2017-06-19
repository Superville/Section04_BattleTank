// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAI.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAI : public AAIController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
};
