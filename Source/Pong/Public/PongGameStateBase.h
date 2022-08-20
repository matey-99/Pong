// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerNumber.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	APongGameStateBase();

	void IncreaseBallSpeed();

	FORCEINLINE float GetStartBallSpeed() const { return StartBallSpeed; }
	FORCEINLINE float GetBallShootConeHalfAngleDeg() const { return BallShootConeHalfAngleDeg; }
	FORCEINLINE float GetCurrentBallSpeed() const { return CurrentBallSpeed; }
	FORCEINLINE EPlayerNumber GetBallOwnerNumber() const { return BallOwnerNumber; }
	FORCEINLINE uint8 GetPlayer1Score() const { return Player1Score; }
	FORCEINLINE uint8 GetPlayer2Score() const { return Player2Score; }

	FORCEINLINE void SetBallOwnerNumber(EPlayerNumber InBallOwnerNumber) { BallOwnerNumber = InBallOwnerNumber; }

	FORCEINLINE void Player1AddPoint() { Player1Score++; }
	FORCEINLINE void Player2AddPoint() { Player2Score++; }

private:
	UPROPERTY(EditAnywhere, Category = "Game Rules")
	float StartBallSpeed;

	UPROPERTY(EditAnywhere, Category = "Game Rules")
	float BallSpeedIncreasePerReflection;

	UPROPERTY(EditAnywhere, Category = "Game Rules")
	float BallShootConeHalfAngleDeg;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	float CurrentBallSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	EPlayerNumber BallOwnerNumber;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	uint8 Player1Score;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	uint8 Player2Score;
};
