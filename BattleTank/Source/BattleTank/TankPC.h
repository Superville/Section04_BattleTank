// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPC.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPC : public APlayerController
{
	GENERATED_BODY()

	float CrosshairScreenPctX = 0.5f;
	float CrosshairScreenPctY = 0.33333f;

	float SightTraceDistance = 1000000.f;

	FVector2D GetCrosshairScreenLocation() const;
	bool GetLookDirection(FVector& out_LookDirection) const;
	bool GetLookHitLocation(FVector& out_HitLocation, FVector LookDirection) const;
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

	// Set target of barrel so that a shot will hit where the crosshair shows in the world
	void AimTowardsCrosshair();
	// Get the hit location of a line trace through the crosshair
	bool GetSightRayHitLocation(FVector& out_HitLocation) const;
};
