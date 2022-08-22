// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "Player/PongPlayerController.h"

#include "Pong.h"
#include "UI/WidgetManager.h"
#include "UI/GamePanelWidget.h"
#include "GameMode/PongGameMode.h"

#include "Kismet/GameplayStatics.h"

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

	APongGameMode* GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GamePanelWidget = GameMode->GetWidgetManager()->GetWidget<UGamePanelWidget>(UGamePanelWidget::StaticClass());
}
