// Fill out your copyright notice in the Description page of Project Settings.

#include "PongGameStateBase.h"

#include "Kismet/GameplayStatics.h"

#include "GamePanelWidget.h"
#include "PongGameModeBase.h"
#include "PongPlayerController.h"

APongGameStateBase::APongGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WinnerNumber = 0;
	Player1Score = 0;
	Player2Score = 0;

	GameTime = 0.0f;
	StartBallSpeed = 1250.0f;
	MaxBallSpeed = 1750.0f;
	BallSpeedIncreasePerReflection = 50.0f;
	BallShootConeHalfAngleDeg = 30.0f;
	CurrentBallSpeed = StartBallSpeed;
	BallOwnerNumber = EPlayerNumber::Player1;
	bBallInGame = false;
	bInPlayState = false;
}

void APongGameStateBase::Reset()
{
	GameTime = 0.0f;
	CurrentBallSpeed = StartBallSpeed;
	BallOwnerNumber = EPlayerNumber::Player1;
	bBallInGame = false;
	bInPlayState = false;

	Player1Score = 0;
	Player2Score = 0;
	WinnerNumber = 0;
}

void APongGameStateBase::IncreaseBallSpeed()
{
	CurrentBallSpeed += BallSpeedIncreasePerReflection;
	CurrentBallSpeed = FMath::Clamp(CurrentBallSpeed, StartBallSpeed, MaxBallSpeed);
}

void APongGameStateBase::Player1AddPoint()
{
	Player1Score++;
	if (Player1Score >= PongGameMode->GetScoreToWin())
	{
		bInPlayState = false;
		WinnerNumber = 1;
		PongGameMode->EndGame();
	}
}

void APongGameStateBase::Player2AddPoint()
{
	Player2Score++;
	if (Player2Score >= PongGameMode->GetScoreToWin())
	{
		bInPlayState = false;
		WinnerNumber = 2;
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
