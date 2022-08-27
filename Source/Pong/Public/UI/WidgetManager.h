// Copyright 2022 Mateusz Michalak. All rights reserved.

#pragma once

#include "Pong.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "WidgetManager.generated.h"

UCLASS()
class PONG_API AWidgetManager : public AActor
{
	GENERATED_BODY()

public:
	/** Returns blueprint widget with given base class. Creates new one if widget doesn't exist */
	template<class T>
	T* GetWidget(UClass* BaseWidgetClass)
	{
		TSubclassOf<UUserWidget>* BlueprintClass = WidgetClasses.Find(BaseWidgetClass);
		if (BlueprintClass)
		{
			UUserWidget** Widget = Widgets.Find(*BlueprintClass);
			if (Widget)
			{
				return CastChecked<T>(*Widget, ECastCheckedType::NullChecked);
			}
			else
			{
				UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), *BlueprintClass);
				Widgets.Add({ *BlueprintClass, UserWidget });

				return CastChecked<T>(UserWidget, ECastCheckedType::NullChecked);
			}
		}
		else
		{
			UE_LOG(LogPong, Fatal, TEXT("Widget blueprint class associated with %s class not found"), *BaseWidgetClass->GetName());
			return nullptr;
		}
	}

	/** Returns blueprint widget class with given base class */
	TSubclassOf<UUserWidget> GetWidgetClass(UClass* BaseWidgetClass);



private:
	/** Contains all widget classes that are use in game.
	 *  Key - base (c++) class of widget
	 *  Value - blueprint class of widget
	 */
	UPROPERTY(EditAnywhere, Category = "Widget")
	TMap<TSubclassOf<UUserWidget>, TSubclassOf<UUserWidget>> WidgetClasses;

	/** Contains all created widgets. 
	 *  Key - blueprint class of widget
	 *  Value - widget object
	 */
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	TMap<TSubclassOf<UUserWidget>, UUserWidget*> Widgets;
};


