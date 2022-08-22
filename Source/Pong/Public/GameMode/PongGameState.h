// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerNumber.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"

class APongGameMode;

/**
 * 
 */
UCLASS()
class PONG_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	APongGameState();

	void Reset();
	void IncreaseBallSpeed();

	FORCEINLINE float GetStartBallSpeed() const { return StartBallSpeed; }
	FORCEINLINE float GetBallShootConeHalfAngleDeg() const { return BallShootConeHalfAngleDeg; }
	FORCEINLINE float GetCurrentBallSpeed() const { return CurrentBallSpeed; }
	FORCEINLINE EPlayerNumber GetBallOwnerNumber() const { return BallOwnerNumber; }
	FORCEINLINE int8 GetWinnerNumber() const { return WinnerNumber; }
	FORCEINLINE uint8 GetPlayer1Score() const { return Player1Score; }
	FORCEINLINE uint8 GetPlayer2Score() const { return Player2Score; }
	FORCEINLINE bool IsInPlayState() const { return bInPlayState; }

	FORCEINLINE void SetBallInGame(bool bInBallInGame) { bBallInGame = bInBallInGame; }
	FORCEINLINE void SetInPlayState(bool bIsPlaying) { bInPlayState = bIsPlaying; }
	FORCEINLINE void SetBallOwnerNumber(EPlayerNumber InBallOwnerNumber) { BallOwnerNumber = InBallOwnerNumber; }

	FORCEINLINE void ResetBallSpeed() { CurrentBallSpeed = StartBallSpeed; }

	void Player1AddPoint();
	void Player2AddPoint();

	void UpdatePlayerGamePanels();

protected:
	// Start of AActor Implementation
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// End of AActor Implementation

private:
	UPROPERTY(VisibleAnywhere)
	APongGameMode* PongGameMode;

	UPROPERTY(EditAnywhere, Category = "Game Rules")
	float StartBallSpeed;

	UPROPERTY(EditAnywhere, Category = "Game Rules")
	float MaxBallSpeed;

	UPROPERTY(EditAnywhere, Category = "Game Rules")
	float BallSpeedIncreasePerReflection;

	UPROPERTY(EditAnywhere, Category = "Game Rules")
	float BallShootConeHalfAngleDeg;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	bool bInPlayState;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	bool bBallInGame;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	float GameTime;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	float CurrentBallSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	EPlayerNumber BallOwnerNumber;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	int8 WinnerNumber;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	uint8 Player1Score;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	uint8 Player2Score;
};
