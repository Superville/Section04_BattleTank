// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPC.h"

ATankPC::ATankPC()
{

}

void ATankPC::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ensure(ControlledTank)) { return; }
	

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);
}

void ATankPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPC::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPC::AimTowardsCrosshair()
{
	ATank* CT = GetControlledTank();
	if (!ensure(CT)) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		// Tell the tank to target that location
		CT->AimAt(HitLocation);
	}
}

bool ATankPC::GetSightRayHitLocation(FVector& out_HitLocation) const
{
	FVector LookDir;
	// Get direction into the world from camera to crosshair world positon
	if (GetLookDirection(LookDir))
	{
		// Linetrace along that direction and see what we hit up to a max range
		return GetLookHitLocation(out_HitLocation, LookDir);
	}
	return false;
}

FVector2D ATankPC::GetCrosshairScreenLocation() const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	return FVector2D(ViewportSizeX*CrosshairScreenPctX, ViewportSizeY*CrosshairScreenPctY);
}

bool ATankPC::GetLookDirection(FVector& out_LookDirection) const
{
	// Find the crosshair position
	auto CrosshairScreenLocation = GetCrosshairScreenLocation();
	
	// Deproject the screen position of the crosshair to a world location
	FVector CrosshairWorldLocation; //ignored
	return DeprojectScreenPositionToWorld(CrosshairScreenLocation.X, CrosshairScreenLocation.Y, CrosshairWorldLocation, out_LookDirection);
}

bool ATankPC::GetLookHitLocation(FVector& out_HitLocation, FVector LookDirection ) const
{
	FHitResult HitResult;
	auto TraceStart = PlayerCameraManager->GetCameraLocation();
	FVector TraceEnd = TraceStart + (LookDirection * SightTraceDistance);
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(GetControlledTank()); // ignore collision with our tank
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CQP))
	{
//		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s  %s"), *HitResult.Location.ToString(), *HitResult.Actor->GetName());
		out_HitLocation = HitResult.Location;
		return true;
	}
	out_HitLocation = FVector::ZeroVector;
	return false;
}