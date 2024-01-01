// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/Button.h"
#include "Kismet/KismetTextLibrary.h"
#include "Resources/BaseResource.h"
#include "Resources/ResourceComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
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

	UPROPERTY(BlueprintReadWrite)
	AActor* SpawnBuildingRef;

	UTextBlock* TextBlockOfGold;
	UTextBlock* TextBlockOfWood;
	UTextBlock* TextBlockOfFood;
	UTextBlock* TextBlockOfNumberOfActuallyPlayerUnits;
	UImage* ImageOfMarquee;
	UOverlay* OverlayOfTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D EndLocation;

	virtual void NativeConstruct();

	UFUNCTION(BlueprintCallable)
	void UpdateResourceValue(EResourceTypes TypeOfResource, int Amount);

	UFUNCTION()
	void StartMarqueeUpdate();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateMarquee();
	
	UFUNCTION()
	void StopMarqueeUpdate();

	UFUNCTION()
	void ShowTable();

	UFUNCTION()
	void HideTable();

	UFUNCTION(BlueprintCallable)
	void UpdateNumberOfPlayerUnits(int& UpdatedNumber);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void FillBar();

	void CheckGoldTB();
	void CheckWoodTB();
	void CheckFoodTB();
	void CheckTableOverlay();
	void CheckActuallyNumberOfPlayerUnitsTB();
	void CheckImageOfMarquee();
};
