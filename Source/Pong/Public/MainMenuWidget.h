// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class USlider;
class UStartGameMenuWidget;

/**
 * 
 */
UCLASS()
class PONG_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void HideAllWidgets();

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnStartGameButtonClicked();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UStartGameMenuWidget> StartGameMenuWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TArray<UUserWidget*> Widgets;

	UPROPERTY(Meta = (BindWidget))
	UButton* StartGameButton;
};
