// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pong.h"
#include "CoreMinimal.h"
#include "PlayerNumber.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

class APongPlayerController;
class APlayerPawn;
class APongCamera;
class AInputReceiver;
class ABall;

/**
 * 
 */
UCLASS()
class PONG_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APongGameModeBase();

	UFUNCTION(BlueprintCallable)
	virtual void StartGame();

	UFUNCTION(BlueprintCallable)
	virtual void PauseGame();

	UFUNCTION(BlueprintCallable)
	virtual void QuitGame();

	UFUNCTION(BlueprintCallable)
	virtual void ShootBall();

	UFUNCTION(BlueprintCallable)
	void OnGetPoint(EPlayerNumber LoserPlayerNumber);

protected:
	virtual void BeginPlay() override;

private:
	void SpawnInputReceiver();

	void SpawnBallAtPlayer(EPlayerNumber PlayerNumber);
	void DestroyBall();

private:
	UPROPERTY(EditAnywhere, Category = "Rules")
	bool bPlayer1Start;

	UPROPERTY(EditAnywhere, Category = "Players")
	TSubclassOf<APlayerPawn> PlayerPawnClass;

	UPROPERTY(VisibleAnywhere, Category = "Players")
	TArray<APongPlayerController*> PlayerControllers;

	UPROPERTY(VisibleAnywhere, Category = "Players")
	TArray<APlayerPawn*> PlayerPawns;

	UPROPERTY(VisibleAnywhere, Category = "Players")
	TArray<FTransform> SpawnTransforms;

	UPROPERTY(VisibleAnywhere, Category = "Players")
	AInputReceiver* InputReceiver;

	UPROPERTY(EditAnywhere, Category = "Camera")
	FTransform DefaultCameraTransform;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	APongCamera* PongCamera;

	UPROPERTY(EditAnywhere, Category = "Ball")
	TSubclassOf<ABall> BallClass;

	UPROPERTY(VisibleAnywhere, Category = "Ball")
	ABall* Ball;

	UPROPERTY(EditAnywhere, Category = "Ball")
	float BallSpawnOffset;
};
