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
	
public:
	// How close can the AI Tank get to the player
	UPROPERTY()
	float AcceptanceRadius = 3000;
};
