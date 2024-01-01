// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/AIControllerEnemy.h"
#include "Framework/BaseRTSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Buildings/BuildingComponent.h"
#include "Units/UnitActions.h"

void AAIControllerEnemy::BeginPlay()
{
	Super::BeginPlay();

	ABaseRTSGameMode* RTSGameMode = Cast<ABaseRTSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	for (AActor* ArrayElements : RTSGameMode->ATownHalls)
	{
		UBuildingComponent* BuildingComponent = Cast<UBuildingComponent>(ArrayElements->GetComponentByClass(UBuildingComponent::StaticClass()));

		IUnitActions* UnitActions = Cast<IUnitActions>(GetPawn());

		if (BuildingComponent->TeamAttitude == ETeamAttitude::Friendly && UnitActions && ArrayElements)
		{
			UnitActions->AttackThisActor(ArrayElements);
		}
	}

}
