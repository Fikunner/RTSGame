// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/AITasks/WorkerBTTask_MoveUnitToLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UWorkerBTTask_MoveUnitToLocation::UWorkerBTTask_MoveUnitToLocation()
{
	NodeName = TEXT("Move Unit To Location");

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UWorkerBTTask_MoveUnitToLocation, BlackboardKey));
}

EBTNodeResult::Type UWorkerBTTask_MoveUnitToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};
	
	AAIController* AIController { OwnerComp.GetAIOwner() };
	const APawn* AIPawn { AIController->GetPawn() };

	const FVector Origin{ AIPawn->GetActorLocation() };

	const UNavigationSystemV1* NavSystem{ UNavigationSystemV1::GetCurrent(GetWorld()) };
	if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UWorkerBTTask_MoveUnitToLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
