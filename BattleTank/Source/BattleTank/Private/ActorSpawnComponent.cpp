// Copyright Steve Superville

#include "BattleTank.h"
#include "ActorSpawnComponent.h"


// Sets default values for this component's properties
UActorSpawnComponent::UActorSpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorSpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	ensure(ClassToSpawn);
	auto NewActor = GetWorld()->SpawnActorDeferred<AActor>(ClassToSpawn, GetComponentTransform());
	if (NewActor == nullptr) { return; }
	NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(NewActor, GetComponentTransform());
}


// Called every frame
void UActorSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

