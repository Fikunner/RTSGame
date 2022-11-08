// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/BaseRTSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

void ABaseRTSGameMode::BeginPlay()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TownHall, ATownHalls);
}

AActor* ABaseRTSGameMode::GetPlayerTownHall()
{
	int FoundIndex;

	for (AActor* ArrayElements : ATownHalls)
	{
		if (ArrayElements->Tags.Find("Player") >= 0)
		{
			FoundIndex = ArrayElements->Tags.Find("Player");
			break;
		}
	}

	return ATownHalls[FoundIndex];
}
