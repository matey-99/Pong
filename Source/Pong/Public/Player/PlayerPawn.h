// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UFloatingPawnMovement;

/**
 * Pawn class for each player
 */
UCLASS()
class PONG_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

	/** Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Moves pawn with given value using UFloatingPawnMovement component */
	void Move(float Value);

	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComponent; }

private:
	/** Main static mesh for player pawn */
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	/** Movement component for player pawn */
	UPROPERTY(EditDefaultsOnly)
	UFloatingPawnMovement* FloatingPawnMovement;
};
