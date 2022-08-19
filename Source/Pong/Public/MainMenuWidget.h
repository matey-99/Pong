// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class USlider;

/**
 * 
 */
UCLASS()
class PONG_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnStartGameButtonClicked();

private:
	UPROPERTY(Meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(Meta = (BindWidget))
	USlider* MaxGameTimeSlider;

	UPROPERTY(Meta = (BindWidget))
	USlider* ScoreToWinSlider;
};
