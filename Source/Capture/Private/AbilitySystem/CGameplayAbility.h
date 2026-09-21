// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class UCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	TArray<FHitResult> GetHitResultsFromSweepLocationData(const FGameplayAbilityTargetDataHandle& TargetDataHandle,float SphereSweepRadius, bool bDrawDebug = false, bool bIgnoreSelf = true) const;
};
