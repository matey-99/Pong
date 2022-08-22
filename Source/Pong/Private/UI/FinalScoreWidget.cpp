// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "UI/FinalScoreWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "GameMode/PongGameMode.h"

void UFinalScoreWidget::NativeConstruct()
{
	PlayAgainButton->OnClicked.AddUniqueDynamic(this, &UFinalScoreWidget::OnPlayAgainButtonClicked);
	BackButton->OnClicked.AddUniqueDynamic(this, &UFinalScoreWidget::OnBackButtonClicked);
}

void UFinalScoreWidget::Init(FString WinnerStr, FString Player1ScoreStr, FString Player2ScoreStr)
{
	WinnerText->SetText(FText::FromString(WinnerStr));
	Player1ScoreText->SetText(FText::FromString(Player1ScoreStr));
	Player2ScoreText->SetText(FText::FromString(Player2ScoreStr));
}

void UFinalScoreWidget::OnPlayAgainButtonClicked()
{
	RemoveFromParent();

	auto GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->Reset();
	GameMode->StartGame();
}

void UFinalScoreWidget::OnBackButtonClicked()
{

}