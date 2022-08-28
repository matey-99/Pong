// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/PlayerNumber.h"
#include "DeathWall.generated.h"

/**
 * Death wall actor
 */
UCLASS()
class PONG_API ADeathWall : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE EPlayerNumber GetConnectedPlayerNumber() const { return ConnectedPlayerNumber; }

private:
	/** Player that is owner of this death wall */
	UPROPERTY(EditAnywhere)
	EPlayerNumber ConnectedPlayerNumber;
};
