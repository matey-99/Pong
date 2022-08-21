// Fill out your copyright notice in the Description page of Project Settings.

#include "StartGameMenuWidget.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

#include "PongGameModeBase.h"
#include "MainMenuWidget.h"

void UStartGameMenuWidget::NativeConstruct()
{
	LocalPlayerVsPlayerButton->OnClicked.AddUniqueDynamic(this, &UStartGameMenuWidget::StartLocalPlayerVsPlayerGame);
	OnlinePlayerVsPlayerButton->OnClicked.AddUniqueDynamic(this, &UStartGameMenuWidget::StartOnlinePlayerVsPlayerGame);
	PlayerVsAIButton->OnClicked.AddUniqueDynamic(this, &UStartGameMenuWidget::StartPlayerVsAIGame);
	BackButton->OnClicked.AddUniqueDynamic(this, &UStartGameMenuWidget::Hide);

	MaxGameTimeSlider->OnValueChanged.AddUniqueDynamic(this, &UStartGameMenuWidget::OnMaxGameTimeSliderValueChanged);
	ScoreToWinSlider->OnValueChanged.AddUniqueDynamic(this, &UStartGameMenuWidget::OnScoreToWinSliderValueChanged);
}

void UStartGameMenuWidget::Init(UMainMenuWidget* InMainMenuWidget)
{
	MainMenuWidget = InMainMenuWidget;

	auto GameMode = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	MaxGameTimeSlider->SetValue(GameMode->GetMaxGameTime());
	MaxGameTimeSlider->SetStepSize(1.0f);
	MaxGameTimeSlider->SetMinValue(30.0f);
	MaxGameTimeSlider->SetMaxValue(360.0f);
	MaxGameTimeText->SetText(FText::FromString(FString::SanitizeFloat(GameMode->GetMaxGameTime())));

	ScoreToWinSlider->SetValue(GameMode->GetScoreToWin());
	ScoreToWinSlider->SetStepSize(1.0f);
	ScoreToWinSlider->SetMinValue(1.0f);
	ScoreToWinSlider->SetMaxValue(24.0f);
	MaxGameTimeText->SetText(FText::FromString(FString::FromInt(GameMode->GetScoreToWin())));
}

void UStartGameMenuWidget::Display()
{
	MainMenuWidget->RemoveFromParent();
	AddToViewport();
}

void UStartGameMenuWidget::Hide()
{
	RemoveFromParent();
	MainMenuWidget->AddToViewport();
}

void UStartGameMenuWidget::StartLocalPlayerVsPlayerGame()
{
	auto GameMode = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->StartGame();
}

void UStartGameMenuWidget::StartOnlinePlayerVsPlayerGame()
{
}

void UStartGameMenuWidget::StartPlayerVsAIGame()
{
}

void UStartGameMenuWidget::OnMaxGameTimeSliderValueChanged(float Value)
{
	auto GameMode = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->SetMaxGameTime(Value);

	MaxGameTimeText->SetText(FText::FromString(FString::FromInt(Value)));
}

void UStartGameMenuWidget::OnScoreToWinSliderValueChanged(float Value)
{
	auto GameMode = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->SetScoreToWin(Value);

	ScoreToWinText->SetText(FText::FromString(FString::FromInt(Value)));
}
