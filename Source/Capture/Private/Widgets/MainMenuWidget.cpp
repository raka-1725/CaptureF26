// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget.h"

#include "MatchMakingWidget.h"
#include "WaitingWidget.h"
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
		if (CGameInstance->IsLoggedIn())
		{
			SwitchToMatchMakingWidget();
		}
	}
	
	LoginButton->OnClicked.AddDynamic(this, &UMainMenuWidget::LoginBtnClicked);
	
	MatchMakingWidget->GetFindAndJoinSessionButtonClickEvent().AddDynamic(this, &UMainMenuWidget::WaitForNewSessionCreate);
	MatchMakingWidget->SetKeyboardFocus();
	
}

void UMainMenuWidget::SwitchToMatchMakingWidget()
{
	MainSwitcher->SetActiveWidget(MatchMakingWidget);
	MatchMakingWidget->SetKeyboardFocus();
}

void UMainMenuWidget::LoginBtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("LoginButtonClicked"));
	if (CGameInstance)
	{
		if (CGameInstance->IsLoggedIn() || CGameInstance->IsLoggingIn())
		{
			UE_LOG(LogTemp, Warning, TEXT("already logged in or logging in"));
			return;
		}
		
		CGameInstance->ClientAuthPortalLogin();
		MainSwitcher->SetActiveWidget(WaitingWidget);
		WaitingWidget->ConfigureWaiting("Logging In", false);
		WaitingWidget->SetKeyboardFocus();
	}
}

void UMainMenuWidget::LoginCompleted(bool bWasSuccessful, const FString& PlayerNickname, const FString& ErrorMsg)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Login successful"));
		
		SwitchToMatchMakingWidget();
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

void UMainMenuWidget::WaitForNewSessionCreate()
{
	MainSwitcher->SetActiveWidget(WaitingWidget);
	WaitingWidget->ConfigureWaiting("Creating Game", true);
	WaitingWidget->ClearAndGetButtonClickedEvent().AddDynamic(this, &UMainMenuWidget::SwitchToMatchMakingWidget);
	WaitingWidget->SetKeyboardFocus();
}

void UMainMenuWidget::WaitForFindAndJoinSession()
{
	MainSwitcher->SetActiveWidget(WaitingWidget);
	WaitingWidget->ConfigureWaiting("Finding Game", true);
	WaitingWidget->ClearAndGetButtonClickedEvent().AddDynamic(this, &UMainMenuWidget::SwitchToMatchMakingWidget);
	WaitingWidget->SetKeyboardFocus();
}
