// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta=(BindWidget))
	class UWidgetSwitcher* MainSwitcher;
	
	UPROPERTY()
	class UCGameInstance* CGameInstance;
	
	//-----//
	//Login//
	//-----//
	
private:
	UPROPERTY(meta=(BindWidget))
	class UButton* LoginButton;
	
	UFUNCTION()
	void LoginBtnClicked();
	
	UFUNCTION()
	void LoginCompleted(bool bWasSuccessful, const FString& PlayerNickname, const FString& ErrorMsg);

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
};
