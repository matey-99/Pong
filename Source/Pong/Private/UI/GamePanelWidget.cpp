// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "UI/GamePanelWidget.h"

#include "Components/TextBlock.h"

void UGamePanelWidget::UpdateGameTimeText(float GameTime)
{
	int32 GameTimeInSeconds = FMath::Floor(GameTime);
	GameTimeText->SetText(FText::FromString(FString::FromInt(GameTimeInSeconds)));
}

void UGamePanelWidget::UpdatePlayer1Score(uint8 Player1Score)
{
	Player1ScoreText->SetText(FText::FromString(FString::FromInt(Player1Score)));
}

void UGamePanelWidget::UpdatePlayer2Score(uint8 Player2Score)
{
	Player2ScoreText->SetText(FText::FromString(FString::FromInt(Player2Score)));
}
