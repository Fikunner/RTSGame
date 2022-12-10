// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Units/BaseWorker.h"
#include "BasePlayerController.h"

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "WorkerBTDecoratorCheckMouseInput.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API UWorkerBTDecoratorCheckMouseInput : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UWorkerBTDecoratorCheckMouseInput();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
