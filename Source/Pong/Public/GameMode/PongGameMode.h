// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerNumber.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"

class APongPlayerController;
class APlayerPawn;
class APongCamera;
class AInputReceiver;
class ABall;
class UMainMenuWidget;
class UFinalScoreWidget;
class AWidgetManager;

/**
 * 
 */
UCLASS()
class PONG_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APongGameMode();

	UFUNCTION(BlueprintCallable)
	virtual void StartGame();

	UFUNCTION(BlueprintCallable)
	virtual void EndGame();

	UFUNCTION(BlueprintCallable)
	void ResetGame();

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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AWidgetManager* GetWidgetManager() const { return WidgetManager; }

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
	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<AWidgetManager> WidgetManagerClass;

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

	AWidgetManager* WidgetManager;

	UMainMenuWidget* MainMenuWidget;
	UFinalScoreWidget* FinalScoreWidget;
};
