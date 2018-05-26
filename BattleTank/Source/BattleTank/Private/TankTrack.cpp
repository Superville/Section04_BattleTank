// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate the slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	// Work out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// Calculate and apply sideways for F = m a
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) * 0.5; // half because there are two tracks
	TankRoot->AddForce(CorrectionForce);
}

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

