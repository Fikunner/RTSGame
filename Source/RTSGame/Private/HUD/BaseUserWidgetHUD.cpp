// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BaseUserWidgetHUD.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"

UBaseUserWidgetHUD::UBaseUserWidgetHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TextBlockOfGold = nullptr;
}

void UBaseUserWidgetHUD::UpdateResourceValue(TEnumAsByte<EResourceTypes> TypeOfResource, int Amount)
{
	const FName TextControlName = FName(TEXT("TB_GoldAmount"));
	if (TextBlockOfGold == nullptr)
	{
		TextBlockOfGold = static_cast<UTextBlock*>(WidgetTree->FindWidget(TextControlName));
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
		
	default:
		{

			break;
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
	/*FVector2D VSubstraction = EndLocation - StartLocation;
	FVector2D VAdd = (EndLocation - StartLocation) + StartLocation;
	double a = 0.f;

	UKismetMathLibrary::BreakVector2D(VSubstraction, VSubstraction.X, VSubstraction.Y);
	double SelectX = UKismetMathLibrary::SelectFloat(StartLocation.X, VAdd.X, VSubstraction.X >= 0);
	double SelectY = UKismetMathLibrary::SelectFloat(StartLocation.Y, VAdd.Y, VSubstraction.Y >= 0);

	EndLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	UWidgetLayoutLibrary::SlotAsCanvasSlot(ImageOfMarquee)->SetPosition(UKismetMathLibrary::MakeVector2D(SelectX, SelectY));
	UWidgetLayoutLibrary::SlotAsCanvasSlot(ImageOfMarquee)->SetSize(FVector2D(100, 100));*/
}

void UBaseUserWidgetHUD::StopMarqueeUpdate()
{
	if (ImageOfMarquee != nullptr)
	{
		ImageOfMarquee->SetVisibility(ESlateVisibility::Collapsed);
	}
}
