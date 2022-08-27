// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class USlider;
class UStartGameMenuWidget;

/**
 * A main menu widget with functionality to start game.
 */
UCLASS()
class PONG_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

	/** Hide all widgets created by main menu widget */
	void HideAllWidgets();

protected:
	// UUserWidget
	virtual void NativeConstruct() override;
	// End of UUserWidget

private:
	/** Called on start game button clicked.
	 *  Removes this widget from viewport and displays start game menu widget
	 */
	UFUNCTION()
	void OnStartGameButtonClicked();

	UFUNCTION()
	void OnQuitGameButtonClicked();

	UFUNCTION()
	void OnHistoryButtonClicked();

private:
	/** All widgets created by main menu widget */
	UPROPERTY(VisibleAnywhere)
	TArray<UUserWidget*> Widgets;

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
