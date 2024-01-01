// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/BaseWorkers.h"
#include "Units/BaseAIControllerUnits.h"

void ABaseWorkers::GoToTownHallAndDepositResources_Implementation(AActor* ResourceRef)
{
}

void ABaseWorkers::RepeatTheMiningAction_Implementation(AActor* ResourceRef)
{
}

void ABaseWorkers::MoveUnitToThisLocation_Implementation(FVector Location)
{
	
}

void ABaseWorkers::BeginPlay()
{
	Super::BeginPlay();

	AIControllerUnits = ABaseUnits::AIControllerUnits;
}

void ABaseWorkers::SetWorkerShouldMine(bool MiningStatus)
{
	isMining = MiningStatus;
}