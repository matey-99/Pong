// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "GameMode/PongGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

#include "Player/PongPlayerController.h"
#include "GameMode/PongGameState.h"
#include "UI/FinalScoreWidget.h"
#include "UI/MainMenuWidget.h"
#include "Player/InputReceiver.h"
#include "Player/PlayerPawn.h"
#include "Player/PongPlayerState.h"
#include "Gameplay/PongCamera.h"
#include "Gameplay/Ball.h"
#include "UI/WidgetManager.h"

APongGameMode::APongGameMode()
{
	ScoreToWin = 6;
	MaxGameTime = 60.0f;
	BallSpawnOffset = 300.0f;

	GameStateClass = APongGameState::StaticClass();
	PlayerControllerClass = APongPlayerController::StaticClass();
	PlayerStateClass = APongPlayerState::StaticClass();
	DefaultPawnClass = nullptr;
	WidgetManagerClass = AWidgetManager::StaticClass();
}

void APongGameMode::StartGame()
{
	SpawnInputReceiver();

	for (TActorIterator<APlayerStart> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		auto PlayerStartActor = *ActorIt;
		SpawnTransforms.Add(PlayerStartActor->GetActorTransform());
	}

	PlayerControllers.Add(Cast<APongPlayerController>(UGameplayStatics::CreatePlayer(GetWorld())));
	PlayerControllers.Add(Cast<APongPlayerController>(UGameplayStatics::CreatePlayer(GetWorld())));

	for (int Index = 0; Index < PlayerControllers.Num(); ++Index)
	{
		FActorSpawnParameters SpawnParams;
		auto PlayerPawn = GetWorld()->SpawnActor<APlayerPawn>(PlayerPawnClass, SpawnTransforms[Index], SpawnParams);
		PlayerControllers[Index]->Possess(PlayerPawn);

		if (Index == 0)
		{
			InputReceiver->SetPlayer1Pawn(PlayerPawn);

			auto StaticMesh = PlayerPawn->GetStaticMeshComponent();
			auto Material = StaticMesh->GetMaterial(0);
			auto DynamicMaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
			DynamicMaterialInstance->SetVectorParameterValue("EmissiveColor", FVector4(0.0f, 1.0f, 0.0f, 1.0f));
			StaticMesh->SetMaterial(0, DynamicMaterialInstance);
		}
		else
		{
			InputReceiver->SetPlayer2Pawn(PlayerPawn);

			auto StaticMesh = PlayerPawn->GetStaticMeshComponent();
			auto Material = StaticMesh->GetMaterial(0);
			auto DynamicMaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
			DynamicMaterialInstance->SetVectorParameterValue("EmissiveColor", FVector4(1.0f, 0.0f, 0.0f, 1.0f));
			StaticMesh->SetMaterial(0, DynamicMaterialInstance);
		}

		PlayerPawns.Add(PlayerPawn);
	}

	auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto PongPC = Cast<APongPlayerController>(PC);
	PongPC->DisplayGamePanel();

	InitCamera();
	SpawnBallAtPlayer(EPlayerNumber::Player1);

	SetInputModeGame();
	
	auto PongGameState = GetGameState<APongGameState>();
	PongGameState->SetInPlayState(true);
}

void APongGameMode::EndGame()
{
	APongGameState* GS = GetGameState<APongGameState>();
	GS->SetInPlayState(false);
	GS->SetBallInGame(false);

	APlayerController* MainPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APongPlayerController* PongMainPC = Cast<APongPlayerController>(MainPC);
	PongMainPC->HideGamePanel();

	UGameplayStatics::RemovePlayer(UGameplayStatics::GetPlayerController(GetWorld(), 2), true);
	UGameplayStatics::RemovePlayer(UGameplayStatics::GetPlayerController(GetWorld(), 1), true);

	DestroyBall();
	DestroyInputReceiver();

	InitCamera();

	FinalScoreWidget = WidgetManager->GetWidget<UFinalScoreWidget>(UFinalScoreWidget::StaticClass());

	int8 P1Score = GS->GetPlayer1Score();
	int8 P2Score = GS->GetPlayer2Score();

	FString WinnerStr;
	if (P1Score > P2Score)
	{
		WinnerStr = "Player 1 Win!";
	}
	else if (P1Score < P2Score)
	{
		WinnerStr = "Player 2 Win!";
	}
	else
	{
		WinnerStr = "Draw!";
	}

	FString Player1ScoreStr = FString::FromInt(GS->GetPlayer1Score());
	FString Player2ScoreStr = FString::FromInt(GS->GetPlayer2Score());

	FinalScoreWidget->Init(WinnerStr, Player1ScoreStr, Player2ScoreStr);
	FinalScoreWidget->AddToViewport();

	SetInputModeUI();
}

void APongGameMode::ShootBall()
{
	APongGameState* PongGameState = GetGameState<APongGameState>();
	if (PongGameState->IsBallInGame())
		return;

	float BallShootConeHalfAngleRad = FMath::DegreesToRadians(PongGameState->GetBallShootConeHalfAngleDeg());
	FVector BallDirection;
	switch (PongGameState->GetBallOwnerNumber())
	{
	default:
	case EPlayerNumber::Player1:
		BallDirection = FMath::VRandCone(FVector::RightVector, BallShootConeHalfAngleRad);
		break;
	case EPlayerNumber::Player2:
		BallDirection = FMath::VRandCone(-FVector::RightVector, BallShootConeHalfAngleRad);
		break;
	}
	BallDirection.Z = 0.0f;

	Ball->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Ball->FindComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);
	Ball->Shoot(BallDirection * PongGameState->GetStartBallSpeed());

	PongGameState->SetBallInGame(true);
}

void APongGameMode::OnGetPoint(EPlayerNumber LoserPlayerNumber)
{
	auto PongGameState = GetGameState<APongGameState>();

	DestroyBall();
	PongGameState->SetBallInGame(false);
	PongGameState->ResetBallSpeed();

	switch (LoserPlayerNumber)
	{
	case EPlayerNumber::Player1:
		PongGameState->Player2AddPoint();
		break;
	case EPlayerNumber::Player2:
		PongGameState->Player1AddPoint();
		break;
	}
	PongGameState->UpdatePlayerGamePanels();

	if (PongGameState->IsInPlayState())
	{
		SpawnBallAtPlayer(LoserPlayerNumber);
	}
}

void APongGameMode::BeginPlay()
{
	Super::BeginPlay();

	WidgetManager = GetWorld()->SpawnActor<AWidgetManager>(WidgetManagerClass);
	check(WidgetManager);

	InitCamera();
	DisplayMainMenu();

	SetInputModeUI();
}

void APongGameMode::ResetGame()
{
	auto PongGameState = GetGameState<APongGameState>();
	PongGameState->ResetStates();

	PlayerControllers.Empty();
	PlayerPawns.Empty();
	SpawnTransforms.Empty();

	if (InputReceiver)
	{
		InputReceiver->Destroy();
		InputReceiver = nullptr;
	}

	if (Ball)
	{
		Ball->Destroy();
		Ball = nullptr;
	}

	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
		MainMenuWidget = nullptr;
	}

	if (FinalScoreWidget)
	{
		FinalScoreWidget->RemoveFromParent();
		FinalScoreWidget = nullptr;
	}
}

void APongGameMode::InitCamera()
{
	if (auto CameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), APongCamera::StaticClass()))
		PongCamera = Cast<APongCamera>(CameraActor);
	else
	{
		UE_LOG(LogPong, Warning, TEXT("Pong Camera Actor not found, creating a new one"));

		FActorSpawnParameters SpawnParams;
		SpawnParams.Name = TEXT("Pong Camera");
		PongCamera = GetWorld()->SpawnActor<APongCamera>(APongCamera::StaticClass(), DefaultCameraTransform, SpawnParams);
	}

	auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetViewTarget(PongCamera);
}

void APongGameMode::DisplayMainMenu()
{
	MainMenuWidget = WidgetManager->GetWidget<UMainMenuWidget>(UMainMenuWidget::StaticClass());
	MainMenuWidget->AddToViewport();
}

void APongGameMode::HideMainMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->HideAllWidgets();

		MainMenuWidget->RemoveFromParent();
		MainMenuWidget = nullptr;
	}
}

void APongGameMode::SpawnInputReceiver()
{
	FActorSpawnParameters SpawnParams;
	InputReceiver = GetWorld()->SpawnActor<AInputReceiver>(AInputReceiver::StaticClass(), SpawnParams);

	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->Possess(InputReceiver);
}

void APongGameMode::DestroyInputReceiver()
{
	if (InputReceiver)
	{
		InputReceiver->Destroy();
		InputReceiver = nullptr;
	}
}

void APongGameMode::SpawnBallAtPlayer(EPlayerNumber PlayerNumber)
{
	FTransform SpawnTransform;
	if (PlayerNumber == EPlayerNumber::Player1)
	{
		SpawnTransform = SpawnTransforms[0];
		FVector SpawnLocation = SpawnTransform.GetTranslation();
		SpawnLocation.Y += BallSpawnOffset;
		SpawnTransform.SetTranslation(SpawnLocation);
	}
	else if (PlayerNumber == EPlayerNumber::Player2)
	{
		SpawnTransform = SpawnTransforms[1];
		FVector SpawnLocation = SpawnTransform.GetTranslation();
		SpawnLocation.Y -= BallSpawnOffset;
		SpawnTransform.SetTranslation(SpawnLocation);
	}

	FActorSpawnParameters SpawnParams;
	Ball = GetWorld()->SpawnActor<ABall>(BallClass, SpawnTransforms[(int)PlayerNumber], SpawnParams);
	Ball->AttachToComponent(PlayerPawns[(int)PlayerNumber]->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	FVector Offset = FVector(BallSpawnOffset, 0.0f, 0.0f);
	Ball->AddActorLocalOffset(Offset);

	auto PongGameState = GetGameState<APongGameState>();
	PongGameState->SetBallOwnerNumber(PlayerNumber);
}

void APongGameMode::DestroyBall()
{
	if (Ball)
	{
		Ball->Destroy();
	}
}

void APongGameMode::SetInputModeGame()
{
	auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetInputMode(FInputModeGameOnly());
	PC->SetIgnoreMoveInput(false);
	PC->SetIgnoreLookInput(false);
	PC->bShowMouseCursor = false;
	PC->bEnableClickEvents = false;
	PC->bEnableMouseOverEvents = false;
}

void APongGameMode::SetInputModeUI()
{
	auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetInputMode(FInputModeUIOnly());
	PC->SetIgnoreMoveInput(true);
	PC->SetIgnoreLookInput(true);
	PC->bShowMouseCursor = true;
	PC->bEnableClickEvents = true;
	PC->bEnableMouseOverEvents = true;
}
