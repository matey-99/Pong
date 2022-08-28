// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHistoryEntryWidget.generated.h"

class UTextBlock;

/**
 * Represents each games history entry in UGameHistoryWidget
 */
UCLASS()
class PONG_API UGameHistoryEntryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UGameHistoryEntryWidget(const FObjectInitializer& ObjectInitializer);

	/** Initializes widget */
	void Init(FDateTime GameDateTime, int8 Player1Score, int8 Player2Score);

private:
	/** TextBlock that displays game date time of given entry */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* GameDateTimeText;

	/** TextBlock that displays player 1 score of given entry */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player1Text;

	/** TextBlock that displays player 2 score of given entry */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player2Text;
};
