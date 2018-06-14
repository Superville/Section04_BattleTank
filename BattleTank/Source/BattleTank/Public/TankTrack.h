// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))//, hidecategories = ("Collision"))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

	UTankTrack();

	virtual void BeginPlay() override;

	UFUNCTION(Category = "Driving")
	TArray<ASprungWheel*> GetWheels() const;

public:
	

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	void DriveTrack(float CurrentThrottle);

	// Max force per track (in Newtons)
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TrackMaxDrivingForce = 40000000.f;
	
};
