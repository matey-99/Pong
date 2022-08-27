// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "GameMode/PongGameState.h"

#include "Kismet/GameplayStatics.h"

#include "UI/GamePanelWidget.h"
#include "GameMode/PongGameMode.h"
#include "Player/PongPlayerController.h"

APongGameState::APongGameState()
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

void APongGameState::ResetStates()
{
	GameTime = 0.0f;
	CurrentBallSpeed = StartBallSpeed;
	BallOwnerNumber = EPlayerNumber::Player1;
	bBallInGame = false;
	bInPlayState = false;

	Player1Score = 0;
	Player2Score = 0;
	WinnerNumber = 0;

	UpdatePlayerGamePanels();
}

void APongGameState::IncreaseBallSpeed()
{
	CurrentBallSpeed += BallSpeedIncreasePerReflection;
	CurrentBallSpeed = FMath::Clamp(CurrentBallSpeed, StartBallSpeed, MaxBallSpeed);
}

void APongGameState::Player1AddPoint()
{
	Player1Score++;
	if (Player1Score >= PongGameMode->GetScoreToWin())
	{
		bInPlayState = false;
		WinnerNumber = 1;
		PongGameMode->EndGame();
	}
}

void APongGameState::Player2AddPoint()
{
	Player2Score++;
	if (Player2Score >= PongGameMode->GetScoreToWin())
	{
		bInPlayState = false;
		WinnerNumber = 2;
		PongGameMode->EndGame();
	}
}

void APongGameState::BeginPlay()
{
	Super::BeginPlay();

	PongGameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void APongGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInPlayState && bBallInGame)
	{
		GameTime += DeltaTime;
		if (GameTime >= PongGameMode->GetMaxGameTime())
		{
			PongGameMode->EndGame();
			return;
		}
	}

	UpdatePlayerGamePanels();
}

void APongGameState::UpdatePlayerGamePanels()
{
	int PlayerNum = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int32 Count = 0; Count < PlayerNum; ++Count)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), Count);
		APongPlayerController* PongPC = Cast<APongPlayerController>(PC);

		UGamePanelWidget* GamePanel = PongPC->GetGamePanelWidget();
		GamePanel->UpdateGameTimeText(GameTime);
		GamePanel->UpdatePlayer1Score(Player1Score);
		GamePanel->UpdatePlayer2Score(Player2Score);
	}
}
