// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"


void AMainMenuPlayerController::AcknowledgePossession(APawn* NewPawn)
{
	Super::AcknowledgePossession(NewPawn);
	MenuWidget = CreateWidget(this, WidgetClass);
	if (MenuWidget)
	{
		MenuWidget->AddToViewport();
	}
	
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//Only affects UI
	SetInputMode(FInputModeUIOnly());
}
