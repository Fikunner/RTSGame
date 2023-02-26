// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "BaseHealthBarWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API UBaseHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	UBaseHealthBarWidgetComponent();
	
	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar(float InPercent);

	UFUNCTION()
	void UpdateHealtBarColor(FLinearColor HealthBarColor);

};
