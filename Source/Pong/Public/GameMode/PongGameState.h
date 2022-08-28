// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerNumber.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"

class APongGameMode;

/**
 * Pong Game State
 */
UCLASS()
class PONG_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	APongGameState();

	/** Reset all states of game */
	void ResetStates();

	/** 
	* Increases ball speed with BallSpeedIncreasePerReflection amount.
	* Clamps value between StartBallSpeed and MaxBallSpeed
	*/
	void IncreaseBallSpeed();



	/** Adds point to Player 1. Checks win conditions and if conditions are met, ends game */
	void Player1AddPoint();

	/** Adds point to Player 2. Checks win conditions and if conditions are met, ends game */
	void Player2AddPoint();

	/** Update Game Panel for each player */
	void UpdatePlayerGamePanels();

	/** Sets ball speed to start value */
	FORCEINLINE void ResetBallSpeed() { CurrentBallSpeed = StartBallSpeed; }

	// Getters
	FORCEINLINE float GetStartBallSpeed() const { return StartBallSpeed; }
	FORCEINLINE float GetBallShootConeHalfAngleDeg() const { return BallShootConeHalfAngleDeg; }
	FORCEINLINE float GetCurrentBallSpeed() const { return CurrentBallSpeed; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EPlayerNumber GetBallOwnerNumber() const { return BallOwnerNumber; }

	FORCEINLINE uint8 GetPlayer1Score() const { return Player1Score; }
	FORCEINLINE uint8 GetPlayer2Score() const { return Player2Score; }
	FORCEINLINE bool IsInPlayState() const { return bInPlayState; }
	FORCEINLINE bool IsBallInGame() const { return bBallInGame; }

	// Setters
	FORCEINLINE void SetBallInGame(bool bInBallInGame) { bBallInGame = bInBallInGame; }
	FORCEINLINE void SetInPlayState(bool bIsPlaying) { bInPlayState = bIsPlaying; }
	FORCEINLINE void SetBallOwnerNumber(EPlayerNumber InBallOwnerNumber) { BallOwnerNumber = InBallOwnerNumber; }

protected:
	// Start of AActor Implementation
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// End of AActor Implementation

private:
	UPROPERTY(VisibleAnywhere)
	APongGameMode* PongGameMode;

	/** Ball speed on start game */
	UPROPERTY(EditAnywhere, Category = "Game Rules")
	float StartBallSpeed;

	/** Max ball speed during game */
	UPROPERTY(EditAnywhere, Category = "Game Rules")
	float MaxBallSpeed;

	/** How much ball speed increase per each ball reflection from players paddles */
	UPROPERTY(EditAnywhere, Category = "Game Rules")
	float BallSpeedIncreasePerReflection;

	/** Range of random ball shooting directions */
	UPROPERTY(EditAnywhere, Category = "Game Rules")
	float BallShootConeHalfAngleDeg;

	/** If game is in play state */
	UPROPERTY(VisibleAnywhere, Category = "Game State")
	bool bInPlayState;

	/** If ball is currently in game */
	UPROPERTY(VisibleAnywhere, Category = "Game State")
	bool bBallInGame;

	/** Current game time */
	UPROPERTY(VisibleAnywhere, Category = "Game State")
	float GameTime;

	/** Current ball speed */
	UPROPERTY(VisibleAnywhere, Category = "Game State")
	float CurrentBallSpeed;

	/** Ball owner number, matter only when one of the players hold ball */
	UPROPERTY(VisibleAnywhere, Category = "Game State")
	EPlayerNumber BallOwnerNumber;

	/** Player 1 current score */
	UPROPERTY(VisibleAnywhere, Category = "Game State")
	uint8 Player1Score;

	/** Player 2 current score */
	UPROPERTY(VisibleAnywhere, Category = "Game State")
	uint8 Player2Score;
};
