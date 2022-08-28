// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "AI/Task/BTTask_ShootBall.h"

#include "GameMode/PongGameMode.h"

#include "Kismet/GameplayStatics.h"

UBTTask_ShootBall::UBTTask_ShootBall()
{
	NodeName = TEXT("Shoot Ball");
}

EBTNodeResult::Type UBTTask_ShootBall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APongGameMode* GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->ShootBall();

	return EBTNodeResult::Succeeded;
}
