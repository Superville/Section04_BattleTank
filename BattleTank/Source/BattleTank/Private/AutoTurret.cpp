// Copyright Steve Superville

#include "BattleTank.h"
#include "AutoTurret.h"


// Sets default values
AAutoTurret::AAutoTurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAutoTurret::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartingHealth;	
}

// Called every frame
void AAutoTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAutoTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAutoTurret::GetHealthPercent() const
{
	return ((float)CurrentHealth / (float)StartingHealth);
}

float AAutoTurret::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	auto DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return Super::TakeDamage(DamageToApply, DamageEvent, EventInstigator, DamageCauser);
}