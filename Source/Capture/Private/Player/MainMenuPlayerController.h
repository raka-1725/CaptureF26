// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void AcknowledgePossession(APawn* NewPawn) override;
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<class UUserWidget> WidgetClass;
	
	UPROPERTY()
	UUserWidget* MenuWidget;
	
};
