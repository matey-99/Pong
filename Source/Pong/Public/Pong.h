// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define ON_SCREEN_DEBUG_MESSAGE(Message) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::White, Message)

DECLARE_LOG_CATEGORY_EXTERN(LogPong, Log, All);

