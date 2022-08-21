// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalScoreWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "PongGameModeBase.h"

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

	auto GameMode = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->Reset();
	GameMode->StartGame();
}

void UFinalScoreWidget::OnBackButtonClicked()
{

}