// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "AI/Task/BTTask_CheckIfBallOwner.h"

#include "GameMode/PongGameState.h"

#include "Kismet/GameplayStatics.h"

UBTTask_CheckIfBallOwner::UBTTask_CheckIfBallOwner()
{
	NodeName = TEXT("Check If Ball Owner");
}

EBTNodeResult::Type UBTTask_CheckIfBallOwner::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APongGameState* GameState = Cast<APongGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (GameState->GetBallOwnerNumber() == EPlayerNumber::Player2)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
}
