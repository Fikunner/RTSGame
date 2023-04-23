// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingComponent.h"
#include "CoreMinimal.h"
#include "Buildings/BaseBuildings.h"
#include "TownHallBuilding.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ATownHallBuilding : public ABaseBuildings
{
	GENERATED_BODY()

	ATownHallBuilding();
	
protected:

	virtual void BeginPlay() override;

	void OnBuildingDestroyed(TEnumAsByte<ETeamAttitude::Type> TeamAttitude);

private:

	UBuildingComponent* BuildingComponent;
};
