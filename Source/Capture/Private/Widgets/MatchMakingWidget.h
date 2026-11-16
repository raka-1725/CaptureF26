// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MatchMakingWidget.generated.h"

/**
 * 
 */
UCLASS()
class UMatchMakingWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* CreateNewSessionButton;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* FindAndJoinSessionButton;
	
	UPROPERTY()
	class UCGameInstance* CGameInstance;
	
	UFUNCTION()
	void CreateNewSessionButtonClicked();
	
	UFUNCTION()
	void FindAndJoinSessionButtonClicked();
};
