// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongCamera.generated.h"

/**
 * Main camera actor class
 */
UCLASS()
class PONG_API APongCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	APongCamera();
};
