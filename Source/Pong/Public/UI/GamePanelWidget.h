// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePanelWidget.generated.h"

class UTextBlock;

/**
 * Widget that is displayed on screen during game.
 * Contains game time and players scores.
 */
UCLASS()
class PONG_API UGamePanelWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** Updates game time text with given GameTime */
	UFUNCTION(BlueprintCallable)
	void UpdateGameTimeText(float GameTime);

	/** Updates player 1 score text with given Player1Score */
	UFUNCTION(BlueprintCallable)
	void UpdatePlayer1Score(uint8 Player1Score);

	/** Updates player 2 score text with given Player2Score */
	UFUNCTION(BlueprintCallable)
	void UpdatePlayer2Score(uint8 Player2Score);

private:
	/** TextBlock that displays current game time */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* GameTimeText;

	/** TextBlock that displays current player 1 score */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player1ScoreText;

	/** TextBlock that displays current player 2 score */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player2ScoreText;
};
