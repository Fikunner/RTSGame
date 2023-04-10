// Fill out your copyright notice in the Description page of Project Settings.

#include "Buildings/BuildingComponent.h"
#include "Units/HUD/BaseHealthBarWidgetComponent.h"

// Sets default values for this component's properties
UBuildingComponent::UBuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


void UBuildingComponent::UpdateHealthBar()
{
	Health = HealthMax;
	 
	if (IsValid(GetOwner()->GetComponentByClass(UBaseHealthBarWidgetComponent::StaticClass())))
	{
		float InPercent = Health / HealthMax;
		
		HealthBarWidgetComponent = Cast<UBaseHealthBarWidgetComponent>(GetOwner()->GetComponentByClass(UBaseHealthBarWidgetComponent::StaticClass()));
		HealthBarWidgetComponent->UpdateHealthBar(InPercent);
	}
}

// Called when the game starts
void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	FTransform RelativeTransform = FTransform(FRotator3d(0,0,0), FVector3d(0,0,100), FVector3d(1,1,1));

	HealthBarWidgetComponent = Cast<UBaseHealthBarWidgetComponent>(GetOwner()->AddComponentByClass(UBaseHealthBarWidgetComponent::StaticClass(), false, RelativeTransform, true));
	HealthBarWidgetComponent->SetDrawSize(HealthBarDrawSize);
	UpdateHealthBar();
}


// Called every frame
void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

