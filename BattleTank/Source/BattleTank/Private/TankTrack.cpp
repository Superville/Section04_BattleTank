// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto Time = GetWorld()->GetTimeSeconds();
	auto N = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%f: UTankTrack::SetThrottle %s - %f"), Time, *N, Throttle);

	Throttle = FMath::Clamp<float>(Throttle, -1.f, 1.f);
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto AppliedLocation = GetComponentLocation();
	UPrimitiveComponent* TankPrimComp = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (TankPrimComp)
	{
		TankPrimComp->AddForceAtLocation(ForceApplied, AppliedLocation);
	}
}

