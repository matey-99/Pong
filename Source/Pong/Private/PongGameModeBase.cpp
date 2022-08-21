// Fill out your copyright notice in the Description page of Project Settings.

#include "PongGameModeBase.h"

#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

#include "PongPlayerController.h"
#include "PongGameStateBase.h"
#include "MainMenuWidget.h"
#include "InputReceiver.h"
#include "PlayerPawn.h"
#include "PongCamera.h"
#include "Ball.h"

APongGameModeBase::APongGameModeBase()
{
	ScoreToWin = 12;
	MaxGameTime = 120.0f;
	BallSpawnOffset = 300.0f;
}

void APongGameModeBase::StartGame()
{
	HideMainMenu();
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

	int PlayerNum = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int32 Count = 0; Count < PlayerNum; ++Count)
	{
		auto PC = UGameplayStatics::GetPlayerController(GetWorld(), Count);
		auto PongPC = Cast<APongPlayerController>(PC);
		PongPC->DisplayGamePanel();
	}

	InitCamera();
	SpawnBallAtPlayer(EPlayerNumber::Player1);
}

void APongGameModeBase::EndGame()
{
	int PlayerNum = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int32 Count = 0; Count < PlayerNum; ++Count)
	{
		auto PC = UGameplayStatics::GetPlayerController(GetWorld(), Count);
		auto PongPC = Cast<APongPlayerController>(PC);
		PongPC->HideGamePanel();
	}
}

void APongGameModeBase::ShootBall()
{
	auto PongGameState = GetGameState<APongGameStateBase>();
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

void APongGameModeBase::OnGetPoint(EPlayerNumber LoserPlayerNumber)
{
	auto PongGameState = GetGameState<APongGameStateBase>();
	switch (LoserPlayerNumber)
	{
	case EPlayerNumber::Player1:
		PongGameState->Player2AddPoint();
		break;
	case EPlayerNumber::Player2:
		PongGameState->Player1AddPoint();
		break;
	}

	DestroyBall();
	PongGameState->ResetBallSpeed();
	SpawnBallAtPlayer(LoserPlayerNumber);

	PongGameState->UpdatePlayerGamePanels();
	PongGameState->SetBallInGame(false);
}

void APongGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	InitCamera();
	DisplayMainMenu();
}

void APongGameModeBase::InitCamera()
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

void APongGameModeBase::DisplayMainMenu()
{
	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass, TEXT("MainMenu"));
	MainMenuWidget->AddToViewport();
}

void APongGameModeBase::HideMainMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->HideAllWidgets();

		MainMenuWidget->RemoveFromParent();
		MainMenuWidget = nullptr;
	}
}

void APongGameModeBase::SpawnInputReceiver()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = "InputReceiver";
	InputReceiver = GetWorld()->SpawnActor<AInputReceiver>(AInputReceiver::StaticClass(), SpawnParams);

	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->Possess(InputReceiver);
}

void APongGameModeBase::SpawnBallAtPlayer(EPlayerNumber PlayerNumber)
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

	auto PongGameState = GetGameState<APongGameStateBase>();
	PongGameState->SetBallOwnerNumber(PlayerNumber);
}

void APongGameModeBase::DestroyBall()
{
	Ball->Destroy();
}
