// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "Pong.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

/**
 * Ball actor
 */
UCLASS()
class PONG_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	ABall();

protected:
	// AActor
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// End of AActor

public:
	/** Adds given velocity to ball */
	void Shoot(FVector Velocity);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UStaticMeshComponent* GetStaticMesh() const { return StaticMesh; }

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	/** Main Static Mesh of ball */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
};
