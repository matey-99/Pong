// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "UI/GameHistory/GameHistoryWidget.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"

#include "Game/PongGameInstance.h"
#include "GameMode/PongGameMode.h"
#include "UI/WidgetManager.h"
#include "UI/MainMenuWidget.h"
#include "UI/GameHistory/GameHistoryEntryWidget.h"

UGameHistoryWidget::UGameHistoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UGameHistoryWidget::NativeConstruct()
{
	BackButton->OnClicked.AddUniqueDynamic(this, &UGameHistoryWidget::Hide);
}

void UGameHistoryWidget::OnBackButtonClicked()
{
}

void UGameHistoryWidget::Init(UMainMenuWidget* InMainMenuWidget)
{
	MainMenuWidget = InMainMenuWidget;

	UPongGameInstance* GameInstance = Cast<UPongGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	APongGameMode* GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	const FGameHistory GameHistory = GameInstance->GetGameHistory();
	for (auto& Entry : GameHistory.Entries)
	{
		TSubclassOf<UUserWidget> EntryWidgetClass = GameMode->GetWidgetManager()->GetWidgetClass(UGameHistoryEntryWidget::StaticClass());
		UGameHistoryEntryWidget* EntryWidget = CreateWidget<UGameHistoryEntryWidget>(GetWorld(), EntryWidgetClass);
		
		EntryWidget->Init(Entry.GameDateTime, Entry.Player1Score, Entry.Player2Score);
		Entries.Add(EntryWidget);
		EntriesScrollBox->AddChild(EntryWidget);
	}
}

void UGameHistoryWidget::Display()
{
	MainMenuWidget->RemoveFromParent();
	AddToViewport();
}

void UGameHistoryWidget::Hide()
{
	Entries.Empty();
	EntriesScrollBox->ClearChildren();

	RemoveFromParent();
	MainMenuWidget->AddToViewport();
}