// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHistoryEntryWidget.generated.h"

class UTextBlock;

/**
 * 
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
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* GameDateTimeText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player1Text;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Player2Text;
};
