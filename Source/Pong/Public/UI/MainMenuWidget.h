// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class USlider;
class UStartGameMenuWidget;

/**
 * Contains functionality to start game, quit game or display games history.
 */
UCLASS()
class PONG_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

protected:
	// UUserWidget
	virtual void NativeConstruct() override;
	// End of UUserWidget

private:
	UFUNCTION()
	void OnStartGameButtonClicked();

	UFUNCTION()
	void OnQuitGameButtonClicked();

	UFUNCTION()
	void OnHistoryButtonClicked();

private:
	/** Button that opens start game menu widget on click */
	UPROPERTY(Meta = (BindWidget))
	UButton* StartGameButton;

	/** Button that quits game on click */
	UPROPERTY(Meta = (BindWidget))
	UButton* QuitGameButton;

	/** Button that displays game history widget on click */
	UPROPERTY(Meta = (BindWidget))
	UButton* HistoryButton;
};
