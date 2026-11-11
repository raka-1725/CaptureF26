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
	UE_LOG(LogTemp, Warning, TEXT("---Server Creating Session---"));
	
	ServerSessionName = GetSessionNameStr();
	FString ServerSessionSearchID = GetSessionSearchIDStr();
	ServerSessionPort = GetSessionPort();
	
	UE_LOG(LogTemp, Warning, TEXT("---Create Session with Name %s, ID: %s, Port: %d---"), *ServerSessionName, *ServerSessionSearchID, ServerSessionPort);
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

