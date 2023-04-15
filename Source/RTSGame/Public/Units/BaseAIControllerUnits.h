// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DetourCrowdAIController.h"
#include "BaseAIControllerUnits.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ABaseAIControllerUnits : public AAIController

{
	GENERATED_BODY()

public:

	ABaseAIControllerUnits(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};
