// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHistoryWidget.generated.h"

class UButton;
class UTextBlock;
class UScrollBox;
class UMainMenuWidget;
class UGameHistoryEntryWidget;

/**
 * Contains games history entries
 */
UCLASS()
class PONG_API UGameHistoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UGameHistoryWidget(const FObjectInitializer& ObjectInitializer);

	/** Initializes widget */
	void Init(UMainMenuWidget* InMainMenuWidget);

	/** Adds this widget to viewport */
	UFUNCTION()
	void Display();

	/** Removes this widget from viewport */
	UFUNCTION()
	void Hide();

protected:
	// UUserWidget
	virtual void NativeConstruct() override;
	// End of UUserWidget

private:
	UFUNCTION()
	void OnBackButtonClicked();

private:
	/** Button that hide this widget and displays main meun on click */
	UPROPERTY(Meta = (BindWidget))
	UButton* BackButton;

	/** ScrollBox that contains all entries */
	UPROPERTY(Meta = (BindWidget))
	UScrollBox* EntriesScrollBox;

	/** All games history entries widgets */
	TArray<UGameHistoryEntryWidget*> Entries;

	UMainMenuWidget* MainMenuWidget;
};
