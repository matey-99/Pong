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
class UMainMenuWidget;
class UFinalScoreWidget;

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
	virtual void EndGame();

	UFUNCTION(BlueprintCallable)
	void Reset();

	UFUNCTION(BlueprintCallable)
	virtual void ShootBall();

	UFUNCTION(BlueprintCallable)
	void OnGetPoint(EPlayerNumber LoserPlayerNumber);

	/* Getters */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE uint8 GetScoreToWin() const { return ScoreToWin; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxGameTime() const { return MaxGameTime; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<APongPlayerController*> GetPlayerControllers() const { return PlayerControllers; }

	/* Setters */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetScoreToWin(uint8 InScoreToWin) { ScoreToWin = InScoreToWin; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetMaxGameTime(float InMaxGameTime) { MaxGameTime = InMaxGameTime; }

protected:
	virtual void BeginPlay() override;

private:

	void InitCamera();

	void DisplayMainMenu();
	void HideMainMenu();

	void SpawnInputReceiver();
	void DestroyInputReceiver();

	void SpawnBallAtPlayer(EPlayerNumber PlayerNumber);
	void DestroyBall();

	void SetInputModeGame();
	void SetInputModeUI();

private:
	UPROPERTY(EditAnywhere, Category = "Rules")
	uint8 ScoreToWin;

	UPROPERTY(EditAnywhere, Category = "Rules")
	float MaxGameTime;

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

	/* Widgets */
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;
	UMainMenuWidget* MainMenuWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UFinalScoreWidget> FinalScoreWidgetClass;
	UFinalScoreWidget* FinalScoreWidget;

};
