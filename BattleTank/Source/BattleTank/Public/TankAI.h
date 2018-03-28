// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAI.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAI : public AAIController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Possess(APawn* P) override;
	
	inline ATank* GetPlayerTank() const;

	void Fire();
	bool IsReadyToFire();

	ATank* ControlledTank = nullptr;
};
