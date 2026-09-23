// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GC_CamShake.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


bool UGC_CamShake::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();
	if (HitResult)
	{
		APlayerController* PC = Cast<APlayerController>(MyTarget->GetOwner());
		//APlayerController* PC = UGameplayStatics::GetPlayerController(MyTarget, 0);
		if (!PC) return true;
		PC->ClientStartCameraShake(CameraShake);
	}
	return true;
}
