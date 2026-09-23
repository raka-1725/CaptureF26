// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GC_HitVFX.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

bool UGC_HitVFX::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();
	if (HitResult)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX, HitResult->ImpactPoint,  UKismetMathLibrary::MakeRotFromX(HitResult->ImpactNormal));
	UE_LOG(LogTemp, Warning, TEXT("VFX c++ gameplay cue"));
	}
	return true;
}
