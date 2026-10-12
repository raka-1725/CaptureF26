// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyBTTask_FindNextPatrolPoint.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMyBTTask_FindNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (BlackBoardComp)
	{
		FVector PatrolCenter = BlackBoardComp->GetValueAsVector(PatrolCenterKey.SelectedKeyName);
		FNavLocation PatrolLocation;
		if (UNavigationSystemV1::GetCurrent(&(OwnerComp))->GetRandomReachablePointInRadius(PatrolCenter, FindRadius, PatrolLocation))
		{
			BlackBoardComp->SetValueAsVector(NextPatrolPointKey.SelectedKeyName, PatrolLocation);
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
