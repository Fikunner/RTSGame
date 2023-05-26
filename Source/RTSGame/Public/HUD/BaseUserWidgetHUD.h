// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/KismetTextLibrary.h"
#include "Resources/BaseResource.h"
#include "Resources/ResourceComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"

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
	UTextBlock* TextBlockOfWood;
	UImage* ImageOfMarquee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D EndLocation;

	UFUNCTION()
	void UpdateResourceValue(EResourceTypes TypeOfResource, int Amount);
	
	UFUNCTION()
	void StartMarqueeUpdate();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateMarquee();
	
	UFUNCTION()
	void StopMarqueeUpdate();
};
