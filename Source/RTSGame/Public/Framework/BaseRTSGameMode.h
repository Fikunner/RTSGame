// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Buildings\BuildingComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseRTSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ABaseRTSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Buildings")
	TSubclassOf<AActor> TownHall;

	AActor* TownHallLocation;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AActor* GetPlayerTownHall();

	UFUNCTION()
	void OnTownHallDestroyed(TEnumAsByte<ETeamAttitude::Type> TeamAttitude);

	UFUNCTION()
	void LoseTheGame();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> ATownHalls;

private:

	class UBuildingComponent* BuildingComponent;

};
