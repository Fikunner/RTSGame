// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Resources/BaseResource.h"
#include "Resources/ResourceComponent.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidgetHUD.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API UBaseUserWidgetHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UBaseUserWidgetHUD(const FObjectInitializer& ObjectInitializer);

	UTextBlock* TextBlockOfGold;

	void UpdateResourceValue(TEnumAsByte<EResourceTypes> TypeOfResource, int Amount);

};
