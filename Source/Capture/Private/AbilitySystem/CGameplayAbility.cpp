// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CGameplayAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FHitResult> UCGameplayAbility::GetHitResultsFromSweepLocationData(
	const FGameplayAbilityTargetDataHandle& TargetDataHandle, float SphereSweepRadius, bool bDrawDebug,
	bool bIgnoreSelf) const
{
	TArray<FHitResult> OutResults;
	TSet<AActor*> HitActors;
	
	for(const TSharedPtr<FGameplayAbilityTargetData>& TargetData : TargetDataHandle.Data)
	{
		FVector StartLocation = TargetData->GetOrigin().GetTranslation();
		FVector EndLocation = TargetData->GetEndPoint();
		
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		
		TArray<AActor*> ActorsToIgnore;
		if (bIgnoreSelf){ActorsToIgnore.Add(GetAvatarActorFromActorInfo());};
		
		TArray<FHitResult> HitResults;
		
		UKismetSystemLibrary::SphereTraceMultiForObjects(this, StartLocation, EndLocation, SphereSweepRadius, ObjectTypes, false, ActorsToIgnore, 
			bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResults, false);
		
		for(const FHitResult& Result : HitResults)
		{
			if (HitActors.Contains(Result.GetActor())){ continue; }
			
			
			HitActors.Add(Result.GetActor());
			
			OutResults.Add(Result);
		}
	}
	
	return OutResults;
}
