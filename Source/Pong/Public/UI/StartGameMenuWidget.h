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
 * Contains game rules settings and player modes choice.
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
	void OnLocalPlayerVsPlayerButtonClicked();

	UFUNCTION()
	void OnPlayerVsAIButtonClicked();

	UFUNCTION()
	void OnMaxGameTimeSliderValueChanged(float Value);

	UFUNCTION()
	void OnScoreToWinSliderValueChanged(float Value);

	UFUNCTION()
	void OnBackButtonClicked();

private:
	/** Button that starts local player vs player game on click */
	UPROPERTY(Meta = (BindWidget))
	UButton* LocalPlayerVsPlayerButton;

	/** Button that starts player vs AI game on click */
	UPROPERTY(Meta = (BindWidget))
	UButton* PlayerVsAIButton;

	/** Slider that changes max game time */
	UPROPERTY(Meta = (BindWidget))
	USlider* MaxGameTimeSlider;

	/** TextBlock that displays max game time */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* MaxGameTimeText;

	/** Slider that changes score needed to win */
	UPROPERTY(Meta = (BindWidget))
	USlider* ScoreToWinSlider;

	/** TextBlock that displays score needed to win */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* ScoreToWinText;

	/** Button that hiding this widget and displays main menu */
	UPROPERTY(Meta = (BindWidget))
	UButton* BackButton;

	/** Main menu widget, initialized in Init method */
	UMainMenuWidget* MainMenuWidget;
};
