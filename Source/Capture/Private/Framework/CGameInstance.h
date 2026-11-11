// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

#include "CGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;
	
	bool IsSessionServer() const;
	
private:
	void CreateSession();
	
	FOnlineSessionSettings GenerateSessionSetting(const FName& SessionName, const FString& SessionSearchID, int Port) const;

	void TerminateSessionServer();
	
	void EndSessionCompleted(FName SessionName, bool bWasSuccessful);
	void OnSessionCreated(FName SessionName, bool bWasSuccessful);
	//-------------------------//
	//	Online Interfaces     //
	//------------------------// 
	
private:
	IOnlineSessionPtr GetSessionInterface() const;
	IOnlineIdentityPtr GetIdentityInterface() const;	
	
	//-------------------------//
	//	Commandline Utilities //
	//------------------------// 
private:
	FString GetSessionNameStr() const;
	FString GetSessionSearchIDStr() const;
	int GetSessionPort() const;
	
	FString GetCommandLineArgAsString(const FName& ParamName) const;
	int GetCommandLineArgAsInt(const FName& ParamName) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "CommandLine Args")
	FName SessionNameKey = "SESSION_NAME";
	
	UPROPERTY(EditDefaultsOnly, Category = "CommandLine Args")
	FName SessionSearchIDKey = "SESSION_SEARCH_ID";
	
	UPROPERTY(EditDefaultsOnly, Category = "CommandLine Args")
	FName SessionPortKey = "SESSION_PORT";
	
	FString ServerSessionName;
	int ServerSessionPort;
	
	//-------------------------//
	//	Map Loading            //
	//------------------------// 
	
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Map")
	TSoftObjectPtr<UWorld> GameLevel;
	
	void LoadLevelandListen(TSoftObjectPtr<UWorld> Level);
};
