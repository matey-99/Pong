// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlayerController.generated.h"

class UGamePanelWidget;

/**
 * Pong Player Controller
 */
UCLASS()
class PONG_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Adds Game Panel Widget to viewport */
	void DisplayGamePanel();

	/** Removes Game Panel Widget from viewport */
	void HideGamePanel();

	FORCEINLINE UGamePanelWidget* GetGamePanelWidget() const { return GamePanelWidget; }

protected:
	// AActor
	virtual void BeginPlay() override;
	// End of AActor

private:
	/** Game Panel Widget instance for this Player Controller */
	UGamePanelWidget* GamePanelWidget;
};
