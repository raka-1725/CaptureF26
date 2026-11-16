// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget.h"
#include "Framework/CGameInstance.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CGameInstance = GetGameInstance<UCGameInstance>();
	if (CGameInstance)
	{
		CGameInstance->OnAuthLoginCompleteDelegate.AddUObject(this, &UMainMenuWidget::LoginCompleted);
	}
	
	LoginButton->OnClicked.AddDynamic(this, &UMainMenuWidget::LoginBtnClicked);
}

void UMainMenuWidget::LoginBtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("LoginButtonClicked"));
	if (CGameInstance)
	{
		CGameInstance->ClientAuthPortalLogin();
	}
}

void UMainMenuWidget::LoginCompleted(bool bWasSuccessful, const FString& PlayerNickname, const FString& ErrorMsg)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Login successful"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Login failed"));
	}
}

FReply UMainMenuWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("Focus Added to path"));
	
	UWidget* ActiveWidget = MainSwitcher->GetActiveWidget();
	
	if (ActiveWidget)
	{
		ActiveWidget->SetKeyboardFocus();
		return FReply::Handled();
	}
	
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}
