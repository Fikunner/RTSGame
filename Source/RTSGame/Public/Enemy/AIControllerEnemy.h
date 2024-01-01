// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/PathFollowingComponent.h"

#include "CoreMinimal.h"
#include "Units/BaseAIControllerUnits.h"
#include "AIControllerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API AAIControllerEnemy : public ABaseAIControllerUnits //, public IUnitActions
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

};
