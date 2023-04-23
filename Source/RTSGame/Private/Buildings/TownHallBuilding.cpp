// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/TownHallBuilding.h"

ATownHallBuilding::ATownHallBuilding()
{
	
}

void ATownHallBuilding::BeginPlay()
{
	Super::BeginPlay();

	BuildingComponent = Cast<UBuildingComponent>(GetComponentByClass(UBuildingComponent::StaticClass()));
	BuildingComponent->OnBuildingDestroyed.AddDynamic(this, &ATownHallBuilding::OnBuildingDestroyed);

}

void ATownHallBuilding::OnBuildingDestroyed(TEnumAsByte<ETeamAttitude::Type> TeamAttitude)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "YOU HAVE LOST");
}
