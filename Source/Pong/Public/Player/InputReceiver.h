// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputReceiver.generated.h"

class APlayerPawn;

/**
 * Input Receiver for Local Player vs Player mode. Manages all inputs and send them to players
 */
UCLASS()
class PONG_API AInputReceiver : public APawn
{
	GENERATED_BODY()

public:
	AInputReceiver();

	/** Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetPlayer1Pawn(APlayerPawn* InPlayer1Pawn) { Player1Pawn = InPlayer1Pawn; }
	FORCEINLINE void SetPlayer2Pawn(APlayerPawn* InPlayer2Pawn) { Player2Pawn = InPlayer2Pawn; }

private:
	/** Moves player 1 with given Value */
	void MovePlayer1(float Value);

	/** Moves player 2 with given Value */
	void MovePlayer2(float Value);

	/** Tries to shoot ball (logic of ball shooting is placed in APongGameMode) */
	void Shoot();

private:
	APlayerPawn* Player1Pawn;
	APlayerPawn* Player2Pawn;
};
