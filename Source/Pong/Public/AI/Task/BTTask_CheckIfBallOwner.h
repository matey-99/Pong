// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CheckIfBallOwner.generated.h"

/**
 * Behavior Tree Task: Check if ball owner
 */
UCLASS()
class PONG_API UBTTask_CheckIfBallOwner : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_CheckIfBallOwner();

protected:
	// UBTTaskNode
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// End of UBTTaskNode

};
