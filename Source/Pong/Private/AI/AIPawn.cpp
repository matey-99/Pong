// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "AI/AIPawn.h"

#include "Gameplay/Ball.h"

#include "Kismet/GameplayStatics.h"

AAIPawn::AAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	MovementSpeed = 1000.0f;
	DistanceToMove = 1200.0f;
}

void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Ball)
	{
		FVector BallLocation = Ball->GetActorLocation();
		if (FVector::Distance(BallLocation, GetActorLocation()) < DistanceToMove
			&& Ball->GetAttachParentActor() == nullptr
			&& Ball->GetStaticMesh()->GetPhysicsLinearVelocity().Y > 0.0f)
		{
			FVector Direction = BallLocation - GetActorLocation();
			Direction.Normalize();

			FVector DeltaLocation = Direction * DeltaTime * MovementSpeed;
			DeltaLocation.Y = 0.0f;
			DeltaLocation.Z = 0.0f;

			AddActorWorldOffset(DeltaLocation, true);
		}
	}
}
