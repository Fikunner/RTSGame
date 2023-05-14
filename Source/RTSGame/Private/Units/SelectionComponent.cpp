// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/SelectionComponent.h"
#include "Components/DecalComponent.h"

// Sets default values for this component's properties
USelectionComponent::USelectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	IndicatorRadius = 256.f;
	IndicatorOffset = FVector(0, 0, 0);
}

void USelectionComponent::ShowSelectionDecal()
{
	DecalComponentRef->SetVisibility(true, false);
	DecalComponentRef->SetHiddenInGame(false, false);
}

void USelectionComponent::HideSelectionDecal()
{
	DecalComponentRef->SetVisibility(false, false);
	DecalComponentRef->SetHiddenInGame(true, false);
}

// Called when the game starts
void USelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	FRotator3d Rotation = FRotator3d(90, 0, 0);
	FVector3d Location = FVector3d(0, 0, 0);
	FVector3d Scale = FVector3d(1, 1, 1);

	FTransform RelativeTransform = FTransform(Rotation, Location, Scale);

	DecalComponentRef = Cast<UDecalComponent>(GetOwner()->AddComponentByClass(UDecalComponent::StaticClass(), false, RelativeTransform, false));
	if (DecalComponentRef)
	{
		FVector DecalScale = FVector(128, IndicatorRadius / DecalComponentRef->DecalSize.Y, IndicatorRadius / DecalComponentRef->DecalSize.Z);

		HideSelectionDecal();
		DecalComponentRef->SetDecalMaterial(DecalMaterial);
		DecalComponentRef->SetRelativeScale3D(DecalScale);
		DecalComponentRef->SetRelativeLocation(IndicatorOffset);
	}

}

// Called every frame
void USelectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

