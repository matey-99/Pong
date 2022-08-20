// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputReceiver.generated.h"

class APlayerPawn;

UCLASS()
class PONG_API AInputReceiver : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInputReceiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetPlayer1Pawn(APlayerPawn* InPlayer1Pawn) { Player1Pawn = InPlayer1Pawn; }
	FORCEINLINE void SetPlayer2Pawn(APlayerPawn* InPlayer2Pawn) { Player2Pawn = InPlayer2Pawn; }

private:
	void MovePlayer1(float Value);
	void MovePlayer2(float Value);
	void Shoot();

private:
	APlayerPawn* Player1Pawn;
	APlayerPawn* Player2Pawn;
};
