// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerNumber.generated.h"

/**
 * Helper enum to describe player number in more clear way
 */
UENUM(BlueprintType)
enum class EPlayerNumber : uint8
{
	None	UMETA(DisplayName = "None"),
	Player1 UMETA(DisplayName = "Player 1"),
	Player2 UMETA(DisplayName = "Player 2")
};
