// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	TankTrack_Left = LeftTrackToSet;
	TankTrack_Right = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!TankTrack_Left || !TankTrack_Right) { return; }
	TankTrack_Left->SetThrottle(Throw);
	TankTrack_Right->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateClockwise(float Throw)
{
	if (!TankTrack_Left || !TankTrack_Right) { return; }
	TankTrack_Left->SetThrottle(Throw);
	TankTrack_Right->SetThrottle(-Throw);
}