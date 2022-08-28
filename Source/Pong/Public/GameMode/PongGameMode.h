// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerNumber.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"

class APongPlayerController;
class APlayerPawn;
class AAIPawn;
class APongCamera;
class AInputReceiver;
class ABall;
class UMainMenuWidget;
class UFinalScoreWidget;
class AWidgetManager;

UENUM(BlueprintType)
enum class EPlayerGameMode : uint8
{
	LocalPlayerVsPlayer			UMETA(DisplayName = "Local Player vs Player"),
	OnlinePlayerVsPlayer		UMETA(DisplayName = "Online Player vs Player"),
	PlayerVsAI					UMETA(DisplayName = "Player vs AI")
};

/**
 * Pong Game Mode
 */
UCLASS()
class PONG_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APongGameMode();

	/** Spawns players, ball, input receiver and starts game */
	UFUNCTION(BlueprintCallable)
	virtual void StartGame(EPlayerGameMode PlayerGameMode = EPlayerGameMode::LocalPlayerVsPlayer);

	/** Destroys players, ball, input receiver and displays final score widget */
	UFUNCTION(BlueprintCallable)
	virtual void EndGame();

	/** Resets whole game mode */
	UFUNCTION(BlueprintCallable)
	void ResetGame();

	/** Shoots ball if one of the players hold it */
	UFUNCTION(BlueprintCallable)
	virtual void ShootBall();

	/** Called on getting point */
	UFUNCTION(BlueprintCallable)
	void OnGetPoint(EPlayerNumber LoserPlayerNumber);

	// Getters
	UFUNCTION(BlueprintCallable)
	FORCEINLINE uint8 GetScoreToWin() const { return ScoreToWin; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxGameTime() const { return MaxGameTime; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<AController*> GetControllers() const { return Controllers; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AWidgetManager* GetWidgetManager() const { return WidgetManager; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EPlayerGameMode GetSelectedPlayerGameMode() const { return SelectedPlayerGameMode; }

	// Setters
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetScoreToWin(uint8 InScoreToWin) { ScoreToWin = InScoreToWin; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetMaxGameTime(float InMaxGameTime) { MaxGameTime = InMaxGameTime; }

protected:
	// AActor
	virtual void BeginPlay() override;
	// End of AActor

private:

	/** Initializes camera, called on BeginPlay */
	void InitCamera();

	/** Displays main menu widget */
	void DisplayMainMenu();

	/** Spawns input reeceiver */
	void SpawnInputReceiver();

	/** Destroys input reeceiver */
	void DestroyInputReceiver();

	/** Spawns players */
	void SpawnPlayers();

	/** Spawns player 1 */
	void SpawnPlayer1();

	/** Spawns enemy AI */
	void SpawnEnemyAI();

	/** Spawns ball and attaches it to player with given number */
	void SpawnBallAtPlayer(EPlayerNumber PlayerNumber);

	/** Destroys ball */
	void DestroyBall();

	/** Sets input mode game only, hides cursor and disables click events */
	void SetInputModeGame();

	/** Sets input mode UI only, shows cursor and enables click events */
	void SetInputModeUI();

private:
	/** Widget Manager class. Instance of this class is spawned on BeginPlay */
	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<AWidgetManager> WidgetManagerClass;

	/** Score needed to win */
	UPROPERTY(EditAnywhere, Category = "Rules")
	uint8 ScoreToWin;

	/** Max game time */
	UPROPERTY(EditAnywhere, Category = "Rules")
	float MaxGameTime;

	/** Player Pawn class. Instances of this class will be representations of players pawns */
	UPROPERTY(EditAnywhere, Category = "Players")
	TSubclassOf<APlayerPawn> PlayerPawnClass;

	/** AI Pawn class. Instances of this class will be representations of AI pawns */
	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AAIPawn> AIPawnClass;

	/** Controllers that are currently in game (doesn't contain input receiver) */
	UPROPERTY(VisibleAnywhere, Category = "Players")
	TArray<AController*> Controllers;

	/** Pawns that are currently in game */
	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
	TArray<APawn*> Pawns;

	/** Spawn transforms for each player, based on APlayerStart instances set on level */
	UPROPERTY(VisibleAnywhere, Category = "Players")
	TArray<FTransform> SpawnTransforms;

	/** Input receiver */
	UPROPERTY(VisibleAnywhere, Category = "Players")
	AInputReceiver* InputReceiver;

	/** Default camera transform for main camera */
	UPROPERTY(EditAnywhere, Category = "Camera")
	FTransform DefaultCameraTransform;

	/** Main camera. If there is no APongCamera instance on level, new one will be created with DefaultCameraTransform value */
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	APongCamera* PongCamera;

	/** Ball class. Instance of this class will be representation of ball in game */
	UPROPERTY(EditAnywhere, Category = "Ball")
	TSubclassOf<ABall> BallClass;

	/** Ball */
	UPROPERTY(VisibleAnywhere, Category = "Ball")
	ABall* Ball;

	/** Ball spawn offset from player */
	UPROPERTY(EditAnywhere, Category = "Ball")
	float BallSpawnOffset;

	/** Selected Playe Game Mode */
	EPlayerGameMode SelectedPlayerGameMode;

	AWidgetManager* WidgetManager;

	UMainMenuWidget* MainMenuWidget;
	UFinalScoreWidget* FinalScoreWidget;
};
