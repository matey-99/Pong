// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePanelWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PONG_API UGamePanelWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateGameTimeText(float GameTime);

	UFUNCTION(BlueprintCallable)
	void UpdatePlayer1Score(uint8 Player1Score);

	UFUNCTION(BlueprintCallable)
	void UpdatePlayer2Score(uint8 Player2Score);

private:
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* GameTimeText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player1ScoreText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player2ScoreText;
};
