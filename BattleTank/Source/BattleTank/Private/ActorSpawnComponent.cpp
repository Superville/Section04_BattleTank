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
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(ClassToSpawn, GetComponentTransform());
	if (SpawnedActor == nullptr) { return; }
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}

AActor* UActorSpawnComponent::GetSpawnedActor() const
{
	return SpawnedActor;
}


// Called every frame
void UActorSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

