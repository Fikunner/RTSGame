// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GenericTeamAgentInterface.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnitActions.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UUnitActions : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSGAME_API IUnitActions
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interfaces")
	void MoveUnitToThisLocation(FVector Location);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interfaces")
	void GatherThisResource(AActor* ResourceRef);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interfaces")
	void InteractWithBuilding(AActor* BuildingRef);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interfaces")
	void AttackThisActor(AActor* ActorToAttack);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interfaces")
	void SetTeam(uint8 const& id);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interfaces")
	FGenericTeamId GetGenericTeamId() const;

};
