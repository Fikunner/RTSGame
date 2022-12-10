// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BaseHUD.h"
#include "Blueprint/UserWidget.h"
#include "HUD/BaseUserWidgetHUD.h"

ABaseHUD::ABaseHUD()
{
	BaseHUDClass = ABaseHUD::StaticClass();
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	if (BaseHUDClass != nullptr)
	{
		UserWidgetHUD = CreateWidget<UBaseUserWidgetHUD>(GetWorld(), BaseHUDClass);

		HUDWidgetRef = Cast<UBaseUserWidgetHUD>(UserWidgetHUD);

		HUDWidgetRef = UserWidgetHUD;

		if (UserWidgetHUD != nullptr)
		{
			UserWidgetHUD->AddToViewport();
		}

	}
}
