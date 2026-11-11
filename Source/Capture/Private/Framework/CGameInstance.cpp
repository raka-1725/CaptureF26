// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/CGameInstance.h"

void UCGameInstance::Init()
{
	Super::Init();
	
	if (GetWorld()->IsEditorWorld()) return;
	
	if (IsSessionServer())
	{
		CreateSession();
	}
	
}

bool UCGameInstance::IsSessionServer() const
{
	return GetWorld() && GetWorld()->GetNetMode() == NM_DedicatedServer;
}

void UCGameInstance::CreateSession()
{
	if (IOnlineSessionPtr SessionPtr = GetSessionInterface())
	{
			
		UE_LOG(LogTemp, Warning, TEXT("---Server Creating Session---"));
		
		ServerSessionName = GetSessionNameStr();
		FString ServerSessionSearchID = GetSessionSearchIDStr();
		ServerSessionPort = GetSessionPort();
		
		UE_LOG(LogTemp, Warning, TEXT("Create Session with Name %s, ID: %s, Port: %d"),
			*ServerSessionName, *ServerSessionSearchID, ServerSessionPort);
		
		SessionPtr->OnCreateSessionCompleteDelegates.RemoveAll(this);
		SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnSessionCreated);
		if (!SessionPtr->CreateSession(0, FName(ServerSessionName), 
			GenerateSessionSetting(FName(ServerSessionName), ServerSessionSearchID, ServerSessionPort)))
		{
			UE_LOG(LogTemp, Warning, TEXT("Session Creation failed"));
			SessionPtr->OnCreateSessionCompleteDelegates.RemoveAll(this);
			TerminateSessionServer();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant find session ptr, terminate"));
		TerminateSessionServer();
	}
}

FOnlineSessionSettings UCGameInstance::GenerateSessionSetting(const FName& SessionName, const FString& SessionSearchID,
	int Port) const
{
	FOnlineSessionSettings OnlineSessionSettings{};
	OnlineSessionSettings.bIsLANMatch = false;
	OnlineSessionSettings.NumPrivateConnections = 10;
	OnlineSessionSettings.bShouldAdvertise = true;
	OnlineSessionSettings.bUsesPresence = false;
	OnlineSessionSettings.bAllowJoinViaPresence = false;
	OnlineSessionSettings.bAllowJoinViaPresenceFriendsOnly = false;
	OnlineSessionSettings.bAllowInvites = true;
	OnlineSessionSettings.bUseLobbiesIfAvailable = false;
	OnlineSessionSettings.bUsesStats = true;
	
	OnlineSessionSettings.Set(SessionNameKey, SessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	OnlineSessionSettings.Set(SessionSearchIDKey, SessionSearchID, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	OnlineSessionSettings.Set(SessionPortKey, Port, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	
	return OnlineSessionSettings;
}

void UCGameInstance::TerminateSessionServer()
{
	if (IOnlineSessionPtr OnlineSessionPtr = GetSessionInterface())
	{
		OnlineSessionPtr->OnEndSessionCompleteDelegates.RemoveAll(this);
		OnlineSessionPtr->OnEndSessionCompleteDelegates.AddUObject(this, &UCGameInstance::EndSessionCompleted);
		if (!OnlineSessionPtr->EndSession(FName(ServerSessionName)))
		{
			FGenericPlatformMisc::RequestExit(false);
		}
	}
	else
	{
		FGenericPlatformMisc::RequestExit(false);
	}
}

void UCGameInstance::EndSessionCompleted(FName SessionName, bool bWasSuccessful)
{
	FGenericPlatformMisc::RequestExit(false);
}

void UCGameInstance::OnSessionCreated(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session %s created successfully"), *SessionName.ToString());
		LoadLevelandListen(GameLevel);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Session %s created successfully"), *SessionName.ToString());
		TerminateSessionServer();
	}
	
	IOnlineSessionPtr SessionPtr = GetSessionInterface();
	if (SessionPtr)
	{
		SessionPtr->OnCreateSessionCompleteDelegates.RemoveAll(this);
	}
}

IOnlineSessionPtr UCGameInstance::GetSessionInterface() const
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		return OnlineSubsystem->GetSessionInterface();
	}
	return nullptr;
}



IOnlineIdentityPtr UCGameInstance::GetIdentityInterface() const
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		return OnlineSubsystem->GetIdentityInterface();
	}
	return nullptr;
}


FString UCGameInstance::GetSessionNameStr() const
{
	return GetCommandLineArgAsString(SessionNameKey);
}

FString UCGameInstance::GetSessionSearchIDStr() const
{
	return GetCommandLineArgAsString(SessionSearchIDKey);
}

int UCGameInstance::GetSessionPort() const
{
	return GetCommandLineArgAsInt(SessionPortKey);
}

FString UCGameInstance::GetCommandLineArgAsString(const FName& ParamName) const
{
	FString OutVal = "";
	FString CommandLineArg = FString::Printf(TEXT("%s="), (*ParamName.ToString()));
	if (FParse::Value(FCommandLine::Get(), *CommandLineArg, OutVal))
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find command line argument :%s"), *(ParamName.ToString()));
	}
	
	return OutVal;
}

int UCGameInstance::GetCommandLineArgAsInt(const FName& ParamName) const
{
	int OutVal = 0;
	FString CommandLineArg = FString::Printf(TEXT("%s="), (*ParamName.ToString()));
	if (FParse::Value(FCommandLine::Get(), *CommandLineArg, OutVal))
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find command line argument :%s"), *(ParamName.ToString()));
	}
	
	return OutVal;
}

void UCGameInstance::LoadLevelandListen(TSoftObjectPtr<UWorld> Level)
{
	const FName LevelURL = FName(FPackageName::ObjectPathToPackageName(Level.ToString()));
	if (LevelURL != "")
	{
		FString TravelStr = FString::Printf(TEXT("%s?listen?port=%d"), *LevelURL.ToString(), ServerSessionPort);
		UE_LOG(LogTemp, Warning, TEXT("Server traveling to %s"), (*TravelStr));
		GetWorld()->ServerTravel(TravelStr);
	}
}


