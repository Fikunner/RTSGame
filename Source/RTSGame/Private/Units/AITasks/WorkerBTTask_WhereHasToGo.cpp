// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/AITasks/WorkerBTTask_WhereHasToGo.h"

UWorkerBTTask_WhereHasToGo::UWorkerBTTask_WhereHasToGo()
{
	NodeName = TEXT("MoveUnitToLocation");

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UWorkerBTTask_WhereHasToGo, BlackboardKey));
}
