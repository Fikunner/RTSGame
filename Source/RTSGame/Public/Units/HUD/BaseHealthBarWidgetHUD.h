// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ProgressBar.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseHealthBarWidgetHUD.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API UBaseHealthBarWidgetHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void UpdateBar(float InPercent);

private:

	class UProgressBar* HealthProgressBar;

};
