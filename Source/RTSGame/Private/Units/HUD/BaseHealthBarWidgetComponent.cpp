// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/HUD/BaseHealthBarWidgetComponent.h"
#include "Units/HUD/BaseHealthBarWidgetHUD.h"

UBaseHealthBarWidgetComponent::UBaseHealthBarWidgetComponent()
{
	
}

void UBaseHealthBarWidgetComponent::UpdateHealthBar(float InPercent)
{
	UBaseHealthBarWidgetHUD* HealthBarWidgetHUD = Cast<UBaseHealthBarWidgetHUD>(GetWidget());
	HealthBarWidgetHUD->UpdateBar(InPercent);
}

void UBaseHealthBarWidgetComponent::UpdateHealtBarColor(FLinearColor HealthBarColor)
{
	UBaseHealthBarWidgetHUD* HealthBarWidgetHUD = Cast<UBaseHealthBarWidgetHUD>(GetWidget());
	HealthBarWidgetHUD->UpdateHealthBarColor(HealthBarColor);
}
