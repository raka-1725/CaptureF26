// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
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

protected:
	virtual void Tick(float DeltaSeconds) override;
private:
	FVector GetTargetPoint() const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targetting")
	float TargetTraceRange;
};
