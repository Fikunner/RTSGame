// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/BaseRTSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

void ABaseRTSGameMode::BeginPlay()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TownHall, ATownHalls);

	for (AActor* ArrayElements : ATownHalls)
	{
		BuildingComponent = Cast<UBuildingComponent>(ArrayElements->GetComponentByClass(UBuildingComponent::StaticClass()));
		BuildingComponent->OnBuildingDestroyed.AddDynamic(this, &ABaseRTSGameMode::OnTownHallDestroyed);
	}
}

AActor* ABaseRTSGameMode::GetPlayerTownHall()
{
	for (const AActor* ArrayElements : ATownHalls)
	{
		if (ArrayElements->Tags.Find("Player") >= 0)
		{
			const int FoundIndex = ArrayElements->Tags.Find("Player");

			TownHallLocation = ATownHalls[FoundIndex];
			break;
		}
	}

	return TownHallLocation;
}

void ABaseRTSGameMode::OnTownHallDestroyed(TEnumAsByte<ETeamAttitude::Type> TeamAttitude)
{
	if (TeamAttitude == ETeamAttitude::Friendly)
	{
		LoseTheGame();
	}
}

void ABaseRTSGameMode::LoseTheGame()
{

}
