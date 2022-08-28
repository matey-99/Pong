// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameHistory.h"
#include "Engine/GameInstance.h"
#include "PongGameInstance.generated.h"

/**
 * Pong Game Instance
 */
UCLASS()
class PONG_API UPongGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPongGameInstance(const FObjectInitializer& ObjectInitializer);

	/** Adds entry to games history */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void AddEntryToGameHistory(const FGameHistoryEntry& Entry) { GameHistory.Entries.Add(Entry); }

	/** Serializes games history to json file (json file path: {ProjectPath}/Saved/GameHistory.json) */
	UFUNCTION(BlueprintCallable)
	void SerializeGameHistory();

	// Getters
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FGameHistory GetGameHistory() const { return GameHistory; }

private:
	UPROPERTY(VisibleAnywhere)
	FGameHistory GameHistory;
};
