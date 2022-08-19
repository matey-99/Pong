// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "Components/Slider.h"

void UMainMenuWidget::NativeConstruct()
{
	StartGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnStartGameButtonClicked);
}

void UMainMenuWidget::OnStartGameButtonClicked()
{

}
