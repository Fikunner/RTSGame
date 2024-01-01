// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BaseUserWidgetHUD.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Units/BaseUnit.h"
#include "Units/BaseUnitComponent.h"

void UBaseUserWidgetHUD::NativeConstruct()
{
	Super::NativeConstruct(); 

	CheckGoldTB();
	CheckWoodTB();
	CheckFoodTB();
	CheckTableOverlay();
	CheckImageOfMarquee();
}

void UBaseUserWidgetHUD::UpdateResourceValue(EResourceTypes TypeOfResource, int Amount)
{
	switch (TypeOfResource)
	{
		case EResourceTypes::Gold:
		{
			if (TextBlockOfGold)
			{
				TextBlockOfGold->SetText(UKismetTextLibrary::Conv_IntToText(Amount, false, true, 2));
			}
		
			break;	
		}
	
		case EResourceTypes::Wood:
		{
			if (TextBlockOfWood)
			{
				TextBlockOfWood->SetText(UKismetTextLibrary::Conv_IntToText(Amount, false, true, 2));
			}

			break;
		}

		case EResourceTypes::Food:
		{
			if (TextBlockOfWood)
			{
				TextBlockOfFood->SetText(UKismetTextLibrary::Conv_IntToText(Amount, false, true, 2));
			}

			break;
		}
	}
}

void UBaseUserWidgetHUD::StartMarqueeUpdate()
{
	StartLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	ImageOfMarquee->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UBaseUserWidgetHUD::UpdateMarquee_Implementation()
{

}

void UBaseUserWidgetHUD::StopMarqueeUpdate()
{
	if (ImageOfMarquee)
	{
		ImageOfMarquee->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBaseUserWidgetHUD::ShowTable()
{
	OverlayOfTable->SetVisibility(ESlateVisibility::Visible);
}

void UBaseUserWidgetHUD::HideTable()
{
	if (OverlayOfTable)
	{
		OverlayOfTable->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBaseUserWidgetHUD::UpdateNumberOfPlayerUnits(int& UpdatedNumber)
{
	CheckActuallyNumberOfPlayerUnitsTB();

	UpdatedNumber = 0;
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseUnit::StaticClass(), FoundActors);

	for (AActor* ArrayElement : FoundActors)
	{
		UBaseUnitComponent* UnitComponent = Cast<UBaseUnitComponent>(ArrayElement->GetComponentByClass(UBaseUnitComponent::StaticClass()));

		if (UnitComponent->TeamAttitude == ETeamAttitude::Friendly)
		{
			UpdatedNumber++;
		}
	}

	TextBlockOfNumberOfActuallyPlayerUnits->SetText(UKismetTextLibrary::Conv_IntToText(UpdatedNumber));
}

void UBaseUserWidgetHUD::FillBar_Implementation()
{

}

void UBaseUserWidgetHUD::CheckGoldTB()
{
	const FName TextControlNameGold = FName(TEXT("TB_GoldAmount"));
	if (!TextBlockOfGold)
	{
		TextBlockOfGold = StaticCast<UTextBlock*>(WidgetTree->FindWidget(TextControlNameGold));
	}
}

void UBaseUserWidgetHUD::CheckWoodTB()
{
	const FName TextControlNameWood = FName(TEXT("TB_WoodAmount"));
	if (!TextBlockOfWood)
	{
		TextBlockOfWood = StaticCast<UTextBlock*>(WidgetTree->FindWidget(TextControlNameWood));
	}
}

void UBaseUserWidgetHUD::CheckFoodTB()
{
	const FName TextControlNameFood = FName(TEXT("TB_FoodAmount"));
	if (!TextBlockOfFood)
	{
		TextBlockOfFood = StaticCast<UTextBlock*>(WidgetTree->FindWidget(TextControlNameFood));
	}
}

void UBaseUserWidgetHUD::CheckTableOverlay()
{
	const FName TextControlName = FName(TEXT("TableOverlay"));
	if (!OverlayOfTable)
	{
		OverlayOfTable = StaticCast<UOverlay*>(WidgetTree->FindWidget(TextControlName));
	}
}

void UBaseUserWidgetHUD::CheckActuallyNumberOfPlayerUnitsTB()
{
	const FName TextControlName = FName(TEXT("TB_ActuallyNumberOfPlayerUnits"));
	if (!TextBlockOfNumberOfActuallyPlayerUnits)
	{
		TextBlockOfNumberOfActuallyPlayerUnits = StaticCast<UTextBlock*>(WidgetTree->FindWidget(TextControlName));
	}
}

void UBaseUserWidgetHUD::CheckImageOfMarquee()
{
	const FName TextControlName = FName(TEXT("Img_Marquee"));
	if (!ImageOfMarquee)
	{
		ImageOfMarquee = StaticCast<UImage*>(WidgetTree->FindWidget(TextControlName));
	}
}