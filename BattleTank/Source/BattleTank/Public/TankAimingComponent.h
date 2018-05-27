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
	OutOfAmmo,
};

class UTankBarrel;
class UTankTurret;
class ATankProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	FVector AimDirection;
	bool bValidAimLocation;
	float NextFireTime = 0.f;

	//cheats
	bool bInfiniteAmmo_Cheat;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

public:	
	UTankBarrel * Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ATankProjectile> ProjectileClass;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileSpeed = 8000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FireRatePerSecond = 2.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoCount = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Firing")
	float AzimuthRotationSpeed = 90.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Firing")
	float ElevationRotationSpeed = 90.f;

	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector InAimTargetLocation);
	void UpdateTurretRotation(float DeltaTime);
	void UpdateFiringStatus();

	UFUNCTION(BlueprintCallable)
	int32 GetAmmoLeft() const;
	bool HasAmmo() const;

	bool IsReloading() const;
	bool IsBarrelMoving() const;
	bool IsReadyToFire(bool bReqLocked=false) const;
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
};
