// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/HUD/BaseHealthBarWidgetHUD.h"
#include "Blueprint/WidgetTree.h"

void UBaseHealthBarWidgetHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseHealthBarWidgetHUD::UpdateBar(float InPercent)
{
	const FName TextControlName = FName(TEXT("PB_Health"));
	if (HealthProgressBar == nullptr)
	{
		HealthProgressBar = static_cast<UProgressBar*>(WidgetTree->FindWidget(TextControlName));
	}

	HealthProgressBar->SetPercent(InPercent);

	if (InPercent >= 1 || InPercent <= 0)
	{
		HealthProgressBar->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		HealthProgressBar->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UBaseHealthBarWidgetHUD::UpdateHealthBarColor(FLinearColor HealthBarColor)
{
	const FName TextControlName = FName(TEXT("PB_Health"));
	if (HealthProgressBar == nullptr)
	{
		HealthProgressBar = static_cast<UProgressBar*>(WidgetTree->FindWidget(TextControlName));
	}

	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);
	
}
