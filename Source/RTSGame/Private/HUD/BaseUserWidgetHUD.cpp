// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BaseUserWidgetHUD.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"

UBaseUserWidgetHUD::UBaseUserWidgetHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TextBlockOfGold = nullptr;
}

void UBaseUserWidgetHUD::UpdateResourceValue(EResourceTypes TypeOfResource, int Amount)
{
	const FName TextControlNameGold = FName(TEXT("TB_GoldAmount"));
	if (TextBlockOfGold == nullptr)
	{
		TextBlockOfGold = static_cast<UTextBlock*>(WidgetTree->FindWidget(TextControlNameGold));
	}

	const FName TextControlNameWood = FName(TEXT("TB_WoodAmount"));
	if (TextBlockOfWood == nullptr)
	{
		TextBlockOfWood = static_cast<UTextBlock*>(WidgetTree->FindWidget(TextControlNameWood));
	}

	switch (TypeOfResource)
	{
		case EResourceTypes::Gold:
		{
			if (TextBlockOfGold != nullptr)
			{
				TextBlockOfGold->SetText(UKismetTextLibrary::Conv_IntToText(Amount, false, true, 2));
			}
		
			break;	
		}
	
		case EResourceTypes::Wood:
		{
			if (TextBlockOfWood != nullptr)
			{
				TextBlockOfWood->SetText(UKismetTextLibrary::Conv_IntToText(Amount, false, true, 2));
			}
		}
	}
}

void UBaseUserWidgetHUD::StartMarqueeUpdate()
{
	const FName TextControlName = FName(TEXT("Img_Marquee"));
	if (ImageOfMarquee == nullptr)
	{
		ImageOfMarquee = static_cast<UImage*>(WidgetTree->FindWidget(TextControlName));
	}

	StartLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	ImageOfMarquee->SetVisibility(ESlateVisibility::HitTestInvisible);

}

void UBaseUserWidgetHUD::UpdateMarquee_Implementation()
{

}

void UBaseUserWidgetHUD::StopMarqueeUpdate()
{
	if (ImageOfMarquee != nullptr)
	{
		ImageOfMarquee->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBaseUserWidgetHUD::ShowTable()
{
	const FName TextControlName = FName(TEXT("TableOverlay"));
	if (OverlayOfTable == nullptr)
	{
		OverlayOfTable = static_cast<UOverlay*>(WidgetTree->FindWidget(TextControlName));
	}
	
	OverlayOfTable->SetVisibility(ESlateVisibility::Visible);
}

void UBaseUserWidgetHUD::HideTable()
{
	if (OverlayOfTable != nullptr)
	{
		OverlayOfTable->SetVisibility(ESlateVisibility::Collapsed);
	}
}
