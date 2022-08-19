// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pong.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

class APongPlayerController;
class APlayerPawn;
class APongCamera;
class AInputReceiver;

/**
 * 
 */
UCLASS()
class PONG_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void StartGame();

	UFUNCTION(BlueprintCallable)
	virtual void PauseGame();

	UFUNCTION(BlueprintCallable)
	virtual void QuitGame();

protected:
	virtual void BeginPlay() override;

private:
	void SpawnInputReceiver();
	void SpawnPlayer(int32 Index, FVector WorldLocation);

private:
	UPROPERTY(EditAnywhere, Category = "Players")
	TSubclassOf<APlayerPawn> PlayerPawnClass;

	UPROPERTY(VisibleAnywhere, Category = "Players")
	TArray<APongPlayerController*> PlayerControllers;

	UPROPERTY(VisibleAnywhere, Category = "Players")
	TArray<FTransform> SpawnTransforms;

	UPROPERTY(VisibleAnywhere, Category = "Players")
	AInputReceiver* InputReceiver;

	UPROPERTY(EditAnywhere, Category = "Camera")
	FTransform DefaultCameraTransform;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	APongCamera* PongCamera;
};
