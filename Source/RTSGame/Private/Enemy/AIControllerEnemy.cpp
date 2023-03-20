// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/AIControllerEnemy.h"
#include "BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Buildings/TownHallBuilding.h"

void AAIControllerEnemy::BeginPlay()
{
	Super::BeginPlay();

	IUnitActions* UnitActions = Cast<IUnitActions>(GetPawn());

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATownHallBuilding::StaticClass(), );

	//UnitActions->AttackThisActor();
}
