// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "Game/PongGameInstance.h"

#include "Pong.h"

#include "JsonObjectConverter.h"
#include "Kismet/KismetSystemLibrary.h"

UPongGameInstance::UPongGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FString ProjectSavedDir = UKismetSystemLibrary::GetProjectSavedDirectory();
	FString GameHistoryFile = ProjectSavedDir + "/GameHistory.json";
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*GameHistoryFile))
	{
		FString GameHistoryJson;
		FFileHelper::LoadFileToString(GameHistoryJson, *GameHistoryFile);
		
		if (!FJsonObjectConverter::JsonObjectStringToUStruct(GameHistoryJson, &GameHistory))
		{
			UE_LOG(LogPong, Warning, TEXT("Failed to deserialize game history json file"));
		}
	}
	else
	{
		UE_LOG(LogPong, Warning, TEXT("Game History file not found"));
	}
}

void UPongGameInstance::SerializeGameHistory()
{
	FString ProjectSavedDir = UKismetSystemLibrary::GetProjectSavedDirectory();
	FString GameHistoryFile = ProjectSavedDir + "/GameHistory.json";
	
	FString GameHistoryJson;
	FJsonObjectConverter::UStructToJsonObjectString<FGameHistory>(GameHistory, GameHistoryJson);
	FFileHelper::SaveStringToFile(GameHistoryJson, *GameHistoryFile);
}
