// Copyright Steve Superville

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAI.h"

void ATankAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetPawn())
	{
		return;
	}

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!ensure(PC)) { return; }
	auto PlayerPawn = PC->GetPawn();
	if (!ensure(PlayerPawn)) { return; }

	// Move toward player (PT)
	MoveToActor(PlayerPawn, AcceptanceRadius);

	// Aim toward the player
	AimingComponent->AimAt(PlayerPawn->GetActorLocation());

	// Fire if ready
	if (AimingComponent->IsReadyToFire(true))
	{
		AimingComponent->Fire();
	}
}
