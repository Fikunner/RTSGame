// Fill out your copyright notice in the Description page of Project Settings.

#include "Units/BaseAIControllerUnits.h"

//#include "BehaviorTree/BehaviorTreeComponent.h"
//#include "BehaviorTree/BlackboardComponent.h"
//#include "BehaviorTree/BehaviorTree.h"
//#include "Kismet/GameplayStatics.h"
#include "Navigation/CrowdFollowingComponent.h"

ABaseAIControllerUnits::ABaseAIControllerUnits(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}
