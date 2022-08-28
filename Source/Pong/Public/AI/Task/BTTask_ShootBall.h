// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ShootBall.generated.h"

/**
 * Behavior Tree Task: Shoot ball
 */
UCLASS()
class PONG_API UBTTask_ShootBall : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_ShootBall();

protected:
	// UBTTaskNode
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// End of UBTTaskNode
};
