// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	TankTrack_Left = LeftTrackToSet;
	TankTrack_Right = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(TankTrack_Left && TankTrack_Right)) { return; }
	TankTrack_Left->SetThrottle(Throw);
	TankTrack_Right->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateClockwise(float Throw)
{
	if (!ensure(TankTrack_Left && TankTrack_Right)) { return; }
	TankTrack_Left->SetThrottle(Throw);
	TankTrack_Right->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds();
//	UE_LOG(LogTemp, Warning, TEXT("%f: RequestDirectMove %s - %s"), Time, *GetOwner()->GetName(), *MoveVelocity.ToString());

	auto TankFwd = GetOwner()->GetActorForwardVector();
	auto TankRt = GetOwner()->GetActorRightVector();
	auto DesiredMoveDir = MoveVelocity.GetSafeNormal();

	float MoveDotFwd = DesiredMoveDir | TankFwd;
	IntendMoveForward(MoveDotFwd);

	float MoveDotRight = FVector::DotProduct(TankRt, DesiredMoveDir);
	auto MoveCrossFwd = FVector::CrossProduct(TankFwd, DesiredMoveDir);
//	UE_LOG(LogTemp, Warning, TEXT("%f: RequestDirectMove %s - cross %f / dot %f"), Time, *GetOwner()->GetName(), MoveCrossFwd.Z, MoveDotRight);
	IntendRotateClockwise(MoveCrossFwd.Z);
}
