// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankTrack;
class UTankAimingComponent;
class ATankProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


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
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTrackReferences(UTankTrack* Left_TrackToSet, UTankTrack* Right_TrackToSet);

	void AimAt(FVector InAimTargetLocation);
	bool IsReadyToFire();

	UFUNCTION(BlueprintCallable, Category=TankCombat)
	void Fire();
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ProjectileSpeed = 4000.f;

	UPROPERTY(EditAnywhere, Category = Firing)
	float FireRatePerSecond = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float AzimuthRotationSpeed = 90.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ElevationRotationSpeed = 90.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<ATankProjectile> ProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* AimingComponent = nullptr;

private:
	UTankBarrel* Barrel = nullptr;

	float NextFireTime = 0.f;
};
