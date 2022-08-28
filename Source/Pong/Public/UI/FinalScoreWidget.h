// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FinalScoreWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * Displayed on finished game, contains game result
 */
UCLASS()
class PONG_API UFinalScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Initializes widget, sets text blocks default values */
	void Init(FString WinnerStr, FString Player1ScoreStr, FString Player2ScoreStr);

private:
	UFUNCTION()
	void OnPlayAgainButtonClicked();

	UFUNCTION()
	void OnBackButtonClicked();

protected:
	// UUserWidget interface
	virtual void NativeConstruct() override;
	// End of UUserWidget interface

private:
	/** TextBlock that displays info about a winner (can be: Player 1/2 Win! or Draw!) */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* WinnerText;

	/** TextBlock that displays player 1 final score */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player1ScoreText;

	/** TextBlock that displays player 2 final score */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player2ScoreText;

	/** Button that starts game again with the same rules on click */
	UPROPERTY(Meta = (BindWidget))
	UButton* PlayAgainButton;

	/** Button that hides this widget and display main menu on click */
	UPROPERTY(Meta = (BindWidget))
	UButton* BackButton;
};
