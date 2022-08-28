// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "Player/InputReceiver.h"

#include "Kismet/GameplayStatics.h"

#include "Player/PlayerPawn.h"
#include "GameMode/PongGameMode.h"

AInputReceiver::AInputReceiver()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInputReceiver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MovePlayer1", this, &AInputReceiver::MovePlayer1);
	PlayerInputComponent->BindAxis("MovePlayer2", this, &AInputReceiver::MovePlayer2);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AInputReceiver::Shoot);
}

void AInputReceiver::MovePlayer1(float Value)
{
	if (Player1Pawn)
	{
		Player1Pawn->Move(Value);
	}
}

void AInputReceiver::MovePlayer2(float Value)
{
	if (Player2Pawn)
	{
		Player2Pawn->Move(-Value);
	}
}

void AInputReceiver::Shoot()
{
	auto GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->ShootBall();
}

