// Copyright Steve Superville

#include "BattleTank.h"
#include "SprungWheel.h"
#include "Tank.h"
#include "TankTrack.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Constraint"));
	SetRootComponent(SpringConstraint);
	SpringConstraint->SetRelativeLocation(FVector::ZeroVector);

	AxleComp = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	AxleComp->SetupAttachment(SpringConstraint);

	WheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraint"));
	WheelConstraint->SetupAttachment(AxleComp);

	WheelComp = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	WheelComp->SetupAttachment(AxleComp);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	auto ParentActor = GetAttachParentActor();
	if (ParentActor == nullptr) { return; }

	auto BodyRoot = Cast<UPrimitiveComponent>(ParentActor->GetRootComponent());
	if (BodyRoot == nullptr) { return; }

	SpringConstraint->SetConstrainedComponents(BodyRoot, NAME_None, AxleComp, NAME_None);
	WheelConstraint->SetConstrainedComponents(AxleComp, NAME_None, WheelComp, NAME_None);

	AxleComp->SetMassOverrideInKg(NAME_None, BodyRoot->GetMass() / 60.f);
	WheelComp->SetMassOverrideInKg(NAME_None, BodyRoot->GetMass() / 60.f);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	WheelComp->AddForce(AxleComp->GetForwardVector() * ForceMagnitude);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

