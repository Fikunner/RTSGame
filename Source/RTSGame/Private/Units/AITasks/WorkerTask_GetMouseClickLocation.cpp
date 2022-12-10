// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/AITasks/WorkerTask_GetMouseClickLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetSystemLibrary.h"

UWorkerTask_GetMouseClickLocation::UWorkerTask_GetMouseClickLocation()
{
	NodeName = TEXT("Get Clicked Mouse Location");

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UWorkerTask_GetMouseClickLocation, BlackboardKey));
}

EBTNodeResult::Type UWorkerTask_GetMouseClickLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	FNavLocation Location;

	AAIController* AIController = OwnerComp.GetAIOwner();
	const APawn* AIPawn = AIController->GetPawn();

	const FVector Origin = AIPawn->GetActorLocation();

	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	
	if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Worker task work");

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

FString UWorkerTask_GetMouseClickLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}


