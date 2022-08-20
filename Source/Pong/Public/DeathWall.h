// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerNumber.h"
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
