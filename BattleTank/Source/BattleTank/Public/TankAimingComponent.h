// Copyright Steve Superville

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aligning,
	Locked,
	Unsolved,
};

class UTankBarrel;
class UTankTurret;
class ATankProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	FVector AimNormal;
	bool bValidAimLocation;
	float NextFireTime = 0.f;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Unsolved;

public:	
	UTankBarrel * Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ATankProjectile> ProjectileClass;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FireRatePerSecond = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Firing")
	float AzimuthRotationSpeed = 90.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Firing")
	float ElevationRotationSpeed = 90.f;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector InAimTargetLocation);
	void UpdateTurretRotation(float DeltaTime);
	bool IsReloading();
	bool IsReadyToFire(bool bReqLocked=false);
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
};
