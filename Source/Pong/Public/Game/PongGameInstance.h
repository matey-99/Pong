// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameHistory.h"
#include "Engine/GameInstance.h"
#include "PongGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API UPongGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPongGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void AddEntryToGameHistory(const FGameHistoryEntry& Entry) { GameHistory.Entries.Add(Entry); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FGameHistory GetGameHistory() const { return GameHistory; }

	UFUNCTION(BlueprintCallable)
	void SerializeGameHistory();

private:
	UPROPERTY(VisibleAnywhere)
	FGameHistory GameHistory;
};
