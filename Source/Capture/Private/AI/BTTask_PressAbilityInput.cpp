// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_PressAbilityInput.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Characters/CCharacter.h"


EBTNodeResult::Type UBTTask_PressAbilityInput::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(AIController->GetPawn());
		if (OwnerASC)
		{
			OwnerASC->PressInputID((int32)InputToPress);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

