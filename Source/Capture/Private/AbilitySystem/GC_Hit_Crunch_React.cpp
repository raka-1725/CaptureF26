// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GC_Hit_Crunch_React.h"

#include "Kismet/GameplayStatics.h"
#include "Player/CPlayerCharacter.h"

bool UGC_Hit_Crunch_React::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	UAnimInstance* AnimInstance = Cast<ACPlayerCharacter>(MyTarget)->GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(HitAnimMontage);
	}
	return true;
}
