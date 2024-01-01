// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/BaseUnits.h"
#include "BaseWorkers.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ABaseWorkers : public ABaseUnits
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MoveUnitToThisLocation(FVector Location) ;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GoToTownHallAndDepositResources(AActor* ResourceRef);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RepeatTheMiningAction(AActor* ResourceRef);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetWorkerShouldMine(bool MiningStatus);

	UPROPERTY(BlueprintReadWrite)
	bool isMining;
	
	class ABaseAIControllerUnits* AIControllerUnits;
};
