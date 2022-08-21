// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Slider.h"

#include "PongGameModeBase.h"
#include "StartGameMenuWidget.h"

void UMainMenuWidget::HideAllWidgets()
{
	for (auto Widget : Widgets)
		Widget->RemoveFromParent();

	Widgets.Empty();
}

void UMainMenuWidget::NativeConstruct()
{
	StartGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnStartGameButtonClicked);
}

void UMainMenuWidget::OnStartGameButtonClicked()
{
	auto StartGameMenu = CreateWidget<UStartGameMenuWidget>(GetWorld(), StartGameMenuWidgetClass, TEXT("StartGameMenu"));
	StartGameMenu->Init(this);
	StartGameMenu->Display();

	Widgets.Add(StartGameMenu);
}
