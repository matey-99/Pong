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
 * 
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
	UPROPERTY(Meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(Meta = (BindWidget))
	UScrollBox* EntriesScrollBox;

	TArray<UGameHistoryEntryWidget*> Entries;
	UMainMenuWidget* MainMenuWidget;
};
