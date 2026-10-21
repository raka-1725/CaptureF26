// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TA_GroundPick.h"
#include "Capture/Capture.h"

ATA_GroundPick::ATA_GroundPick()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATA_GroundPick::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (PrimaryPC && PrimaryPC->IsLocalPlayerController())
	{
		SetActorLocation(GetTargetPoint());
	}
}

FVector ATA_GroundPick::GetTargetPoint() const
{
	if (!PrimaryPC || !PrimaryPC->IsLocalController())
	{
		return GetActorLocation();
	}
	
	FVector ViewLocation;
	FRotator ViewRotation;
	
	PrimaryPC->GetPlayerViewPoint(ViewLocation, ViewRotation);
	FVector TraceEnd = ViewLocation + ViewRotation.Vector() * TargetTraceRange;
	
	
	FHitResult TraceResult;
	GetWorld()->LineTraceSingleByChannel(TraceResult, ViewLocation, TraceEnd, ECC_Target);
}
