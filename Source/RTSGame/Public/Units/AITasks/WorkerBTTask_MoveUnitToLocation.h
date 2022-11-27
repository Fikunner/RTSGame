// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "WorkerBTTask_MoveUnitToLocation.generated.h"

/**
 * BTTask for moving a units to location
 */
UCLASS()
class RTSGAME_API UWorkerBTTask_MoveUnitToLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UWorkerBTTask_MoveUnitToLocation();

private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	float SearchRadius { 500.f };

};
