// Copyright Steve Superville

#include "BattleTank.h"
#include "Tank.h"
#include "AutoTurret.h"
#include "TankAimingComponent.h"
#include "TankAI.h"

void ATankAI::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (PossessedTank) {
			// subscribe to tank death event
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAI::OnPossessedTankDeath);
		}
		auto PossessedAutoTurret = Cast<AAutoTurret>(InPawn);
		if (PossessedAutoTurret)
		{
			PossessedAutoTurret->OnDeath.AddUniqueDynamic(this, &ATankAI::OnPossessedAutoTurretDeath);
		}
	}
}

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
	if (!PlayerPawn) { return; }

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

void ATankAI::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAI::OnPossessedAutoTurretDeath()
{
	OnPossessedTankDeath();
}
