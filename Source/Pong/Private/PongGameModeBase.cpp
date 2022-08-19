// Fill out your copyright notice in the Description page of Project Settings.

#include "PongGameModeBase.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

#include "PongPlayerController.h"
#include "PlayerPawn.h"
#include "PongCamera.h"
#include "InputReceiver.h"

void APongGameModeBase::StartGame()
{
}

void APongGameModeBase::PauseGame()
{
}

void APongGameModeBase::QuitGame()
{
}

void APongGameModeBase::BeginPlay()
{
	Super::BeginPlay();

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
		//SpawnParams.Name = FName("Player" + FString::FromInt(Index) + "Pawn");
		auto PlayerPawn = GetWorld()->SpawnActor<APlayerPawn>(PlayerPawnClass, SpawnTransforms[Index], SpawnParams);
		PlayerControllers[Index]->Possess(PlayerPawn);

		if (Index == 0)
			InputReceiver->SetPlayer1Character(PlayerPawn);
		else
			InputReceiver->SetPlayer2Character(PlayerPawn);
	}

	if (auto CameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), APongCamera::StaticClass()))
		PongCamera = Cast<APongCamera>(CameraActor);
	else
	{
		UE_LOG(LogPong, Warning, TEXT("Pong Camera Actor not found, creating a new one"));

		FActorSpawnParameters SpawnParams;
		SpawnParams.Name = TEXT("Pong Camera");

		PongCamera = GetWorld()->SpawnActor<APongCamera>(SpawnParams);
		PongCamera->SetActorTransform(DefaultCameraTransform);
		PongCamera->RegisterAllComponents();
	}

	auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetViewTarget(PongCamera);

	for (auto PlayerController : PlayerControllers)
	{
		FViewTargetTransitionParams ViewTargetTransitionParams;
		PlayerController->SetViewTarget(PongCamera, ViewTargetTransitionParams);
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

void APongGameModeBase::SpawnPlayer(int32 Index, FVector WorldLocation)
{
	auto PlayerController = UGameplayStatics::CreatePlayer(GetWorld());
	PlayerControllers.Add(Cast<APongPlayerController>(PlayerController));
}
