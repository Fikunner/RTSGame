// Fill out your copyright notice in the Description page of Project Settings.

#include "Units/BaseUnit.h"
#include "Units/BaseAIControllerUnits.h"
#include "BasePlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Resources/ResourceComponent.h"
#include "Components/CapsuleComponent.h"
#include "Units/BaseUnitComponent.h"
#include "Units/SelectComponent.h"

ABaseUnit::ABaseUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthBarWidgetComponent = CreateDefaultSubobject<UBaseHealthBarWidgetComponent>("HealthBarWidgetComponent");
	HealthBarWidgetComponent->SetupAttachment(GetCapsuleComponent());

	SelectionComponent = CreateDefaultSubobject<USelectComponent>(TEXT("SelectionComponent"));
	BaseUnitComponent = CreateDefaultSubobject<UBaseUnitComponent>("BaseUnitComponent");
}

void ABaseUnit::BeginPlay()
{
	BaseUnitComponent = Cast<UBaseUnitComponent>(GetComponentByClass(UBaseUnitComponent::StaticClass()));

	//AIControllerUnits = Cast<ABaseAIControllerUnits>(GetController());
	//PathFollowingComponent = AIControllerUnits->GetPathFollowingComponent();
}

void ABaseUnit::Tick(float DeltaTime)
{
}

void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

void ABaseUnit::OnMoveCompletedMoveUnitToThisLocation(FAIRequestID RequestID, const FPathFollowingResult& Result)
{

}

void ABaseUnit::SetTeam_Implementation(uint8 const& id)
{
	TeamId = FGenericTeamId(id);
}

FGenericTeamId ABaseUnit::GetGenericTeamId_Implementation() const
{
	return TeamId;
}

void ABaseUnit::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	if (BaseUnitComponent->TeamAttitude == ETeamAttitude::Friendly)
	{
		PlayerController->ClickSelectThisActor(this);
	}
}

void ABaseUnit::SelectThis()
{
	//SelectionComponent->ShowSelectionDecal();
}

void ABaseUnit::DeselectThis()
{
	//SelectionComponent->HideSelectionDecal();
}
