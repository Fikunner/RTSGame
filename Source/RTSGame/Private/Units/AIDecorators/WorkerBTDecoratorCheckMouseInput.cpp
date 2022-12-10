// Fill out your copyright notice in the Description page of Project Settings.

#include "Units/AIDecorators/WorkerBTDecoratorCheckMouseInput.h"
#include "Units/BaseAIControllerUnits.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"

UWorkerBTDecoratorCheckMouseInput::UWorkerBTDecoratorCheckMouseInput()
{

}

bool UWorkerBTDecoratorCheckMouseInput::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool IsSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (!IsSuccess) { return false; }
	
	ABaseWorker* Worker = Cast<ABaseWorker>(OwnerComp.GetAIOwner()->GetPawn());

	if (Worker)
	{
		
	}

	return true;
}
