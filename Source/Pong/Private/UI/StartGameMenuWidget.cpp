// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "UI/StartGameMenuWidget.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

#include "GameMode/PongGameMode.h"
#include "UI/MainMenuWidget.h"

UStartGameMenuWidget::UStartGameMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UStartGameMenuWidget::NativeConstruct()
{
	LocalPlayerVsPlayerButton->OnClicked.AddUniqueDynamic(this, &UStartGameMenuWidget::OnLocalPlayerVsPlayerButtonClicked);
	PlayerVsAIButton->OnClicked.AddUniqueDynamic(this, &UStartGameMenuWidget::OnPlayerVsAIButtonClicked);
	BackButton->OnClicked.AddUniqueDynamic(this, &UStartGameMenuWidget::OnBackButtonClicked);

	MaxGameTimeSlider->OnValueChanged.AddUniqueDynamic(this, &UStartGameMenuWidget::OnMaxGameTimeSliderValueChanged);
	ScoreToWinSlider->OnValueChanged.AddUniqueDynamic(this, &UStartGameMenuWidget::OnScoreToWinSliderValueChanged);
}

void UStartGameMenuWidget::Init(UMainMenuWidget* InMainMenuWidget)
{
	MainMenuWidget = InMainMenuWidget;

	auto GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	MaxGameTimeSlider->SetValue(GameMode->GetMaxGameTime());
	MaxGameTimeSlider->SetStepSize(1.0f);
	MaxGameTimeSlider->SetMinValue(30.0f);
	MaxGameTimeSlider->SetMaxValue(360.0f);
	MaxGameTimeText->SetText(FText::FromString(FString::SanitizeFloat(GameMode->GetMaxGameTime())));

	ScoreToWinSlider->SetValue(GameMode->GetScoreToWin());
	ScoreToWinSlider->SetStepSize(1.0f);
	ScoreToWinSlider->SetMinValue(1.0f);
	ScoreToWinSlider->SetMaxValue(24.0f);
	ScoreToWinText->SetText(FText::FromString(FString::FromInt(GameMode->GetScoreToWin())));
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

void UStartGameMenuWidget::OnLocalPlayerVsPlayerButtonClicked()
{
	RemoveFromParent();

	MainMenuWidget->RemoveFromParent();
	MainMenuWidget = nullptr;

	auto GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->StartGame(EPlayerGameMode::LocalPlayerVsPlayer);
}

void UStartGameMenuWidget::OnPlayerVsAIButtonClicked()
{
	RemoveFromParent();

	MainMenuWidget->RemoveFromParent();
	MainMenuWidget = nullptr;

	auto GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->StartGame(EPlayerGameMode::PlayerVsAI);
}

void UStartGameMenuWidget::OnMaxGameTimeSliderValueChanged(float Value)
{
	auto GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->SetMaxGameTime(Value);

	MaxGameTimeText->SetText(FText::FromString(FString::FromInt(Value)));
}

void UStartGameMenuWidget::OnScoreToWinSliderValueChanged(float Value)
{
	auto GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->SetScoreToWin(Value);

	ScoreToWinText->SetText(FText::FromString(FString::FromInt(Value)));
}

void UStartGameMenuWidget::OnBackButtonClicked()
{
	Hide();
}
