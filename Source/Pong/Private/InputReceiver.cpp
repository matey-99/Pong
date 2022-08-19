// Fill out your copyright notice in the Description page of Project Settings.

#include "InputReceiver.h"

#include "PlayerPawn.h"

// Sets default values
AInputReceiver::AInputReceiver()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AInputReceiver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInputReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInputReceiver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MovePlayer1", this, &AInputReceiver::MovePlayer1);
	PlayerInputComponent->BindAxis("MovePlayer2", this, &AInputReceiver::MovePlayer2);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AInputReceiver::Shoot);
}

void AInputReceiver::MovePlayer1(float Value)
{
	Player1Character->Move(Value);
}

void AInputReceiver::MovePlayer2(float Value)
{
	Player2Character->Move(-Value);
}

void AInputReceiver::Shoot()
{
}
