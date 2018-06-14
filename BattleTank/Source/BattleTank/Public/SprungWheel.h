// Copyright Steve Superville

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class UStaticMeshComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* SpringConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* AxleComp = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* WheelConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* WheelComp = nullptr;
	
	void SetupConstraint();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Category = "Driving")
	void AddDrivingForce(float ForceMagnitude);
	
	
};
