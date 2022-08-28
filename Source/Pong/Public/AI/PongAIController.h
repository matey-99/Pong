// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PongAIController.generated.h"

class UBehaviorTree;
class UBehaviorTreeComponent;
class UBlackboardComponent;
class ABall;

/**
 * Pong AI Controller
 */
UCLASS()
class PONG_API APongAIController : public AAIController
{
	GENERATED_BODY()

public:
	APongAIController();

protected:
	// AActor
	virtual void BeginPlay() override;
	// End of AActor

	// AController
	virtual void OnPossess(APawn* InPawn) override;
	// End of AController

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
	ABall* Ball;
};
