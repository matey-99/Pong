// Fill out your copyright notice in the Description page of Project Settings.

#include "PongPlayerController.h"

#include "Pong.h"
#include "GamePanelWidget.h"

void APongPlayerController::DisplayGamePanel()
{
	GamePanelWidget->AddToViewport();
}

void APongPlayerController::HideGamePanel()
{
	GamePanelWidget->RemoveFromParent();
}

void APongPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GamePanelWidgetClass != nullptr)
	{
		GamePanelWidget = CreateWidget<UGamePanelWidget>(GetWorld(), GamePanelWidgetClass, TEXT("GamePanel"));
	}
	else
	{
		UE_LOG(LogPong, Error, TEXT("GamePanelWidgetClass is nullptr, cannot create GamePanelWidget for PongPlayerController"));
	}
}
