// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MatchMakingWidget.h"

#include "MainMenuWidget.h"
#include "Framework/CGameInstance.h"
#include "Components/Button.h"

void UMatchMakingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CGameInstance = GetGameInstance<UCGameInstance>();
	
	CreateNewSessionButton->OnClicked.AddDynamic(this, &UMatchMakingWidget::CreateNewSessionButtonClicked);
	FindAndJoinSessionButton->OnClicked.AddDynamic(this, &UMatchMakingWidget::FindAndJoinSessionButtonClicked);
}

void UMatchMakingWidget::CreateNewSessionButtonClicked()
{
	if (CGameInstance)
	{
		CGameInstance->RequestCreateNewSession();
	}
}

void UMatchMakingWidget::FindAndJoinSessionButtonClicked()
{
	if (CGameInstance)
	{
		CGameInstance->TryFindAndJoinSession();
	}
}
