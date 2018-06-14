// Copyright Steve Superville

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ActorSpawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UActorSpawnComponent : public USceneComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor> ClassToSpawn;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	AActor* SpawnedActor = nullptr;

public:	
	// Sets default values for this component's properties
	UActorSpawnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetSpawnedActor() const;
		
	
};
