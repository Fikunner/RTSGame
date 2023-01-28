// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BaseUserWidgetHUD.h"
#include "Blueprint/WidgetTree.h"


UBaseUserWidgetHUD::UBaseUserWidgetHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBP(TEXT("/Game/RTS/Core/HUD/WBP_HUD"));

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
