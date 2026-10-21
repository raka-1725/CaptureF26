// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GenericTeamAgentInterface.h"
#include "TA_GroundPick.generated.h"

/**
 * 
 */
UCLASS()
class ATA_GroundPick : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	ATA_GroundPick();
	
	virtual void ConfirmTargetingAndContinue() override;

protected:
	virtual void Tick(float DeltaSeconds) override;
private:
	FVector GetTargetPoint() const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targetting")
	float TargetTraceRange = 2000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targetting")
	float TargetRadius = 200.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	bool bShouldDrawDebug = true;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSet<TEnumAsByte<ETeamAttitude::Type>> TargetTeamAttitude;
};
