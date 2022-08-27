// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameHistory.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FGameHistoryEntry
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	FDateTime GameDateTime;

	UPROPERTY(VisibleAnywhere)
	int8 Player1Score;

	UPROPERTY(VisibleAnywhere)
	int8 Player2Score;
};

USTRUCT(BlueprintType)
struct FGameHistory
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TArray<FGameHistoryEntry> Entries;
};
