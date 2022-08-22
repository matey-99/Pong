// Copyright 2022 Mateusz Michalak. All rights reserved.

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
	UGamePanelWidget* GamePanelWidget;
};
