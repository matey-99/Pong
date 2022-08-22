// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#define ON_SCREEN_DEBUG_MESSAGE(Message) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::White, Message)

DECLARE_LOG_CATEGORY_EXTERN(LogPong, Log, All);

