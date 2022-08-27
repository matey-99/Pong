// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "UI/MainMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "Components/Slider.h"

#include "UI/WidgetManager.h"
#include "GameMode/PongGameMode.h"
#include "UI/StartGameMenuWidget.h"
#include "UI/GameHistory/GameHistoryWidget.h"

void UMainMenuWidget::HideAllWidgets()
{
	for (auto Widget : Widgets)
		Widget->RemoveFromParent();

	Widgets.Empty();
}

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMainMenuWidget::NativeConstruct()
{
	StartGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnStartGameButtonClicked);
	QuitGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnQuitGameButtonClicked);
	HistoryButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnHistoryButtonClicked);
}

void UMainMenuWidget::OnStartGameButtonClicked()
{
	APongGameMode* GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	UStartGameMenuWidget* StartGameMenu = GameMode->GetWidgetManager()->GetWidget<UStartGameMenuWidget>(UStartGameMenuWidget::StaticClass());
	StartGameMenu->Init(this);
	StartGameMenu->AddToViewport();

	RemoveFromParent();

	Widgets.Add(StartGameMenu);
}

void UMainMenuWidget::OnQuitGameButtonClicked()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Type::Quit, false);
}

void UMainMenuWidget::OnHistoryButtonClicked()
{
	APongGameMode* GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	UGameHistoryWidget* GameHistory = GameMode->GetWidgetManager()->GetWidget<UGameHistoryWidget>(UGameHistoryWidget::StaticClass());
	GameHistory->Init(this);
	GameHistory->AddToViewport();

	RemoveFromParent();

	Widgets.Add(GameHistory);
}
