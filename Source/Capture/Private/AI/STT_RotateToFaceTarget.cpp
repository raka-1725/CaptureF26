// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STT_RotateToFaceTarget.h"

#include "AIController.h"
#include "StateTreeExecutionContext.h"


EStateTreeRunStatus FSTT_RotateToFaceTarget::EnterState(FStateTreeExecutionContext& context, const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = context.GetInstanceData(*this);
	if (!InstanceData.AIController)
	{
		UE_LOG(LogTemp,Warning, TEXT("Cant find ai cont"))
		return EStateTreeRunStatus::Failed;
	}
	
	if (!InstanceData.Target)
	{
		UE_LOG(LogTemp,Warning, TEXT("Cant find target"))
		return EStateTreeRunStatus::Failed;
	}
	
	InstanceData.AIController->SetFocus(InstanceData.Target);
	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FSTT_RotateToFaceTarget::Tick(FStateTreeExecutionContext& context, const float DeltaTime) const
{
	FInstanceDataType& InstanceData = context.GetInstanceData(*this);
	if (!InstanceData.AIController)
	{
		UE_LOG(LogTemp,Warning, TEXT("Cant find ai cont"))
		return EStateTreeRunStatus::Failed;
	}
	
	const FVector PawnDir = InstanceData.AIController->GetPawn()->GetActorForwardVector();
	const FVector FocalPoint = InstanceData.AIController->GetFocalPointForPriority(EAIFocusPriority::Gameplay);
	
	if (FocalPoint != FAISystem::InvalidLocation)
	{
		const float AngleCos = PawnDir.CosineAngle2D(FocalPoint - InstanceData.AIController->GetPawn()->GetActorLocation());
		const float PrecisionCos = FMath::Cos(FMath::DegreesToRadians(InstanceData.PrecisionDegrees));
		if (AngleCos >= PrecisionCos && InstanceData.bShouldSuccessWhenFinished)
		{
			return EStateTreeRunStatus::Succeeded;
		}
	}
	
	return EStateTreeRunStatus::Running;
}

void FSTT_RotateToFaceTarget::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	if (!InstanceData.AIController)
	{
		UE_LOG(LogTemp,Warning, TEXT("Cant find ai cont"))
		return;
	}
	
	InstanceData.AIController->ClearFocus(EAIFocusPriority::Gameplay);
}
