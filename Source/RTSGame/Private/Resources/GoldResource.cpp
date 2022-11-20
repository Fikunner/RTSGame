// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/GoldResource.h"
#include "Resources/ResourceComponent.h"

AGoldResource::AGoldResource()
{
	ABaseResource::ResourceComponent->TypeOfResource = EResourceTypes::Gold;
	ABaseResource::ResourceComponent->TimeIsCanBeMined = 10;
	ABaseResource::ResourceComponent->NumberOfResourcesToGive = 5;
}

void AGoldResource::BeginPlay()
{
	Super::BeginPlay();

}
