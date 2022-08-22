// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/PlayerNumber.h"
#include "DeathWall.generated.h"

UCLASS()
class PONG_API ADeathWall : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE EPlayerNumber GetConnectedPlayerNumber() const { return ConnectedPlayerNumber; }

private:
	UPROPERTY(EditAnywhere)
	EPlayerNumber ConnectedPlayerNumber;
};
