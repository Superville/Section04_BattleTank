// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "SprungWheel.h"
#include "ActorSpawnComponent.h"

UTankTrack::UTankTrack()
{
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

}

void UTankTrack::SetThrottle(float Throttle) 
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	ensure(Wheels.Num() > 0);
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (int i = 0; i < Wheels.Num(); i++ )
	{
		auto w = Wheels[i];
		w->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> Results;

	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (int i = 0; i < Children.Num(); i++)
	{
		auto SpawnComp = Cast<UActorSpawnComponent>(Children[i]);
		if (SpawnComp == nullptr) {continue;}
		auto WheelActor = Cast<ASprungWheel>(SpawnComp->GetSpawnedActor());
		if (WheelActor == nullptr) {continue;}
		
		Results.Add(WheelActor);
	}

	return Results;
}