// Fill out your copyright notice in the Description page of Project Settings.

#include "PongGameStateBase.h"

#include "Kismet/GameplayStatics.h"

#include "GamePanelWidget.h"
#include "PongGameModeBase.h"
#include "PongPlayerController.h"

APongGameStateBase::APongGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GameTime = 0.0f;
	StartBallSpeed = 1000.0f;
	BallSpeedIncreasePerReflection = 50.0f;
	BallShootConeHalfAngleDeg = 30.0f;
	CurrentBallSpeed = StartBallSpeed;
	BallOwnerNumber = EPlayerNumber::Player1;
	bBallInGame = false;
}

void APongGameStateBase::IncreaseBallSpeed()
{
	CurrentBallSpeed += BallSpeedIncreasePerReflection;
}

void APongGameStateBase::Player1AddPoint()
{
	Player1Score++;
	if (Player1Score >= PongGameMode->GetScoreToWin())
	{
		PongGameMode->EndGame();
	}
}

void APongGameStateBase::Player2AddPoint()
{
	Player2Score++;
	if (Player2Score >= PongGameMode->GetScoreToWin())
	{
		PongGameMode->EndGame();
	}
}

void APongGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	PongGameMode = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

void APongGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bBallInGame)
	{
		GameTime += DeltaTime;
		if (GameTime >= PongGameMode->GetMaxGameTime())
		{
			PongGameMode->EndGame();
			return;
		}

		UpdatePlayerGamePanels();
	}
}

void APongGameStateBase::UpdatePlayerGamePanels()
{
	int PlayerNum = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int32 Count = 0; Count < PlayerNum; ++Count)
	{
		auto PC = UGameplayStatics::GetPlayerController(GetWorld(), Count);
		auto PongPC = Cast<APongPlayerController>(PC);

		auto GamePanel = PongPC->GetGamePanelWidget();
		GamePanel->UpdateGameTimeText(GameTime);
		GamePanel->UpdatePlayer1Score(Player1Score);
		GamePanel->UpdatePlayer2Score(Player2Score);
	}
}
