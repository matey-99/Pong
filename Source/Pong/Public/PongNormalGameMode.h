// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PongGameModeBase.h"
#include "PongNormalGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongNormalGameMode : public APongGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void StartGame() override;
	virtual void PauseGame() override;
	virtual void QuitGame() override;
};
