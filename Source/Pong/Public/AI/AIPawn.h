// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

class ABall;

/**
 * Pawn class for each AI controller
 */
UCLASS()
class PONG_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	AAIPawn();

	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComponent; }

	FORCEINLINE void SetBall(ABall* InBall) { Ball = InBall; }

protected:
	// AActor
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// End of AActor

private:
	/** Main static mesh for player pawn */
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float DistanceToMove;

	UPROPERTY(VisibleAnywhere)
	ABall* Ball;
};
