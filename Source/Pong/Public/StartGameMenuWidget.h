// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartGameMenuWidget.generated.h"

class UButton;
class USlider;
class UTextBlock;
class UMainMenuWidget;

/**
 * 
 */
UCLASS()
class PONG_API UStartGameMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	/* Start of UUserWidget Interface */
	virtual void NativeConstruct() override;
	/* End of UUserWidget Interface */

public:
	void Init(UMainMenuWidget* InMainMenuWidget);

	UFUNCTION()
	void Display();

	UFUNCTION()
	void Hide();

	UFUNCTION()
	void StartLocalPlayerVsPlayerGame();

	UFUNCTION()
	void StartOnlinePlayerVsPlayerGame();

	UFUNCTION()
	void StartPlayerVsAIGame();

	UFUNCTION()
	void OnMaxGameTimeSliderValueChanged(float Value);

	UFUNCTION()
	void OnScoreToWinSliderValueChanged(float Value);

private:
	UPROPERTY(Meta = (BindWidget))
	UButton* LocalPlayerVsPlayerButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* OnlinePlayerVsPlayerButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* PlayerVsAIButton;

	UPROPERTY(Meta = (BindWidget))
	USlider* MaxGameTimeSlider;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* MaxGameTimeText;

	UPROPERTY(Meta = (BindWidget))
	USlider* ScoreToWinSlider;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* ScoreToWinText;

	UPROPERTY(Meta = (BindWidget))
	UButton* BackButton;

	UMainMenuWidget* MainMenuWidget;
};
