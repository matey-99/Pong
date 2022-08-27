// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "UI/WidgetManager.h"

TSubclassOf<UUserWidget> AWidgetManager::GetWidgetClass(UClass* BaseWidgetClass)
{
	TSubclassOf<UUserWidget>* BlueprintClass = WidgetClasses.Find(BaseWidgetClass);
	if (BlueprintClass)
	{
		return *BlueprintClass;
	}
	else
	{
		UE_LOG(LogPong, Fatal, TEXT("Widget blueprint class associated with %s class not found"), *BaseWidgetClass->GetName());
		return nullptr;
	}
}
