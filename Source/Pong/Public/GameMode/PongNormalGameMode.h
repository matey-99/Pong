// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PongGameMode.h"
#include "PongNormalGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongNormalGameMode : public APongGameMode
{
	GENERATED_BODY()
	
public:
	virtual void StartGame() override;
	virtual void EndGame() override;
};
