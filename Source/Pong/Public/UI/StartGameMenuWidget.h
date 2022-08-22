// Copyright 2022 Mateusz Michalak. All rights reserved.

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

public:
	UStartGameMenuWidget(const FObjectInitializer& ObjectInitializer);

	/** Initializes widget, sets sliders default values */
	void Init(UMainMenuWidget* InMainMenuWidget);

	/** Adds this widget to viewport */
	UFUNCTION()
	void Display();

	/** Removes this widget from viewport */
	UFUNCTION()
	void Hide();

protected:
	// UUserWidget
	virtual void NativeConstruct() override;
	// End of UUserWidget

private:
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
