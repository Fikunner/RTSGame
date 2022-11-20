// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/BaseResource.h"
#include "GoldResource.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API AGoldResource : public ABaseResource
{
	GENERATED_BODY()
	
public:

	AGoldResource();

protected:

	void BeginPlay() override;

private:

	UResourceComponent* ResourceComponent;
};
