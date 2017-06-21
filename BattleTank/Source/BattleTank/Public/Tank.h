// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	

	void UpdateTurretRotation(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* AimingComponent = nullptr;

public:	
	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category=Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);
	
	void AimAt(FVector InAimTargetLocation);
	UFUNCTION(BlueprintCallable, Category=TankCombat)
	void Fire();
	
	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileSpeed = 4000.f;

	UPROPERTY(EditAnywhere, Category = Firing)
	float AzimuthRotationSpeed = 90.f;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ElevationRotationSpeed = 90.f;

};
