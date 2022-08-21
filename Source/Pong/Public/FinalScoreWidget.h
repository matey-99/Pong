// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FinalScoreWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PONG_API UFinalScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
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
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* WinnerText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player1ScoreText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player2ScoreText;

	UPROPERTY(Meta = (BindWidget))
	UButton* PlayAgainButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* BackButton;
};
