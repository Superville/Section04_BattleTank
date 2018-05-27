// Copyright Steve Superville

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAI.generated.h"

class UTankAimingComponent;

/**
 * Controls AI Tank behavior
 */
UCLASS()
class BATTLETANK_API ATankAI : public AAIController
{
	GENERATED_BODY()

	virtual void Tick(float DeltaTime) override;

protected:
	// How close can the AI Tank get to the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;

public:
	
};
