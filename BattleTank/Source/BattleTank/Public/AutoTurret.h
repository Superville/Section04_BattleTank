// Copyright Steve Superville

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AutoTurret.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAutoTurretDelegate);

UCLASS()
class BATTLETANK_API AAutoTurret : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
	
public:
	// Sets default values for this pawn's properties
	AAutoTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	FAutoTurretDelegate OnDeath;
};
