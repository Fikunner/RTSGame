// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Units/BaseAIControllerUnits.h"
#include "Units/BaseWorker.h"

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "WorkerTask_GetMouseClickLocation.generated.h"

/**
 *  BTTask for get a mouse actions clicked
 */
UCLASS()
class RTSGAME_API UWorkerTask_GetMouseClickLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	
	UWorkerTask_GetMouseClickLocation();

private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	TArray<AActor*> SelectedActors;

	float SearchRadius = 1000.f;

	class ABaseWorker* Worker;

};
