// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resources/BaseResource.h"
#include "Resources/ResourceComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	ABaseHUD();

	UPROPERTY()
	class UBaseUserWidgetHUD* UserWidgetHUD;

	UPROPERTY(BlueprintReadWrite)
	class UBaseUserWidgetHUD* HUDWidgetRef;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UBaseUserWidgetHUD> BaseHUDClass;



};
