// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "Gameplay/Ball.h"

#include "Gameplay/DeathWall.h"
#include "Player/PlayerPawn.h"
#include "GameMode/PongGameMode.h"
#include "GameMode/PongGameState.h"

#include "Kismet/GameplayStatics.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMesh;

	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetEnableGravity(false);
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->OnComponentHit.AddUniqueDynamic(this, &ABall::OnHit);

}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PongGameState = Cast<APongGameState>(UGameplayStatics::GetGameState(GetWorld()));
	float Speed = PongGameState->GetCurrentBallSpeed();

	FVector CurrentVelocity = StaticMesh->GetPhysicsLinearVelocity();
	CurrentVelocity.Normalize();

	if (FMath::Abs(CurrentVelocity.Y) < 0.5f)
	{
		float Sign = FMath::Sign(CurrentVelocity.Y);
		CurrentVelocity.Y = 0.5f * Sign;
	}

	CurrentVelocity *= Speed;


	StaticMesh->SetPhysicsLinearVelocity(CurrentVelocity);
}

void ABall::Shoot(FVector Velocity)
{
	StaticMesh->SetPhysicsLinearVelocity(Velocity);
}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<APlayerPawn>(OtherActor))
	{
		auto PongGameState = Cast<APongGameState>(UGameplayStatics::GetGameState(GetWorld()));
		PongGameState->IncreaseBallSpeed();
	}
	else if (auto DeathWall = Cast<ADeathWall>(OtherActor))
	{
		auto GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->OnGetPoint(DeathWall->GetConnectedPlayerNumber());
	}
}
