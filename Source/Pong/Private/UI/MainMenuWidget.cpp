// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "UI/MainMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Slider.h"

#include "UI/WidgetManager.h"
#include "GameMode/PongGameMode.h"
#include "UI/StartGameMenuWidget.h"

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
