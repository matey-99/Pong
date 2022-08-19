// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

// Sets default values
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(GetRootComponent());

	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->OnComponentHit.AddUniqueDynamic(this, &ABall::OnHit);

	StaticMesh->SetPhysicsLinearVelocity(FVector(0, 1, 0) * 300);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector NewDirection = Hit.Normal;
	NewDirection.Z = 0.0f;
	StaticMesh->SetPhysicsLinearVelocity(NewDirection * 300);
}
