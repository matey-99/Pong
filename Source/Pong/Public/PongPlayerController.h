// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlayerController.generated.h"

class UGamePanelWidget;

/**
 * 
 */
UCLASS()
class PONG_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void DisplayGamePanel();
	void HideGamePanel();

	FORCEINLINE UGamePanelWidget* GetGamePanelWidget() const { return GamePanelWidget; }

protected:
	// AActor interface
	virtual void BeginPlay() override;
	// End of AActor interface

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UGamePanelWidget> GamePanelWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UGamePanelWidget* GamePanelWidget;
};
