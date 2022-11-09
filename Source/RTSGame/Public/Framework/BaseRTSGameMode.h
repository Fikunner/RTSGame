// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

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

	AActor* TownHallLoc;

	UFUNCTION(BlueprintCallable)
	AActor* GetPlayerTownHall(AActor* TownHallLocation);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> ATownHalls;

private:

};
