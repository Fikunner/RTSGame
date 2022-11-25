// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/GoldResource.h"
#include "Resources/ResourceComponent.h"
#include "Units/BaseWorker.h"

AGoldResource::AGoldResource()
{

}

void AGoldResource::BeginPlay()
{
	Super::BeginPlay();

	ResourceComponent = Cast<UResourceComponent>(GetComponentByClass(UResourceComponent::StaticClass()));

	ResourceComponent->GetOwner()->FindComponentByClass<UResourceComponent>()->TypeOfResource = EResourceTypes::Gold;
	ResourceComponent->GetOwner()->FindComponentByClass<UResourceComponent>()->TimeIsCanBeMined = 10;
	ResourceComponent->GetOwner()->FindComponentByClass<UResourceComponent>()->NumberOfResourcesToGive = 5;

}
