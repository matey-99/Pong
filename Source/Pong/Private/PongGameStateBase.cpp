// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameStateBase.h"

APongGameStateBase::APongGameStateBase()
{
	StartBallSpeed = 1000.0f;
	BallSpeedIncreasePerReflection = 50.0f;
	BallShootConeHalfAngleDeg = 30.0f;
	CurrentBallSpeed = StartBallSpeed;
	BallOwnerNumber = EPlayerNumber::Player1;
}

void APongGameStateBase::IncreaseBallSpeed()
{
	CurrentBallSpeed += BallSpeedIncreasePerReflection;
}
