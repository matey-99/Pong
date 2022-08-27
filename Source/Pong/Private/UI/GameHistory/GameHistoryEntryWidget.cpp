// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "UI/GameHistory/GameHistoryEntryWidget.h"

#include "Components/TextBlock.h"

UGameHistoryEntryWidget::UGameHistoryEntryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UGameHistoryEntryWidget::Init(FDateTime GameDateTime, int8 Player1Score, int8 Player2Score)
{
	GameDateTimeText->SetText(FText::FromString(GameDateTime.ToString()));
	Player1Text->SetText(FText::FromString(FString::FromInt(Player1Score)));
	Player2Text->SetText(FText::FromString(FString::FromInt(Player2Score)));
}