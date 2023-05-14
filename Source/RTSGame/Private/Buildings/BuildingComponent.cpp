// Fill out your copyright notice in the Description page of Project Settings.

#include "Buildings/BuildingComponent.h"
#include "Units/HUD/BaseHealthBarWidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetArrayLibrary.h"

// Sets default values for this component's properties
UBuildingComponent::UBuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Health = HealthMax;

}


void UBuildingComponent::UpdateHealthBar()
{	 
	if (IsValid(HealthBarWidgetComponent))
	{
		float CurrentHealth = Health / HealthMax;
		
		HealthBarWidgetComponent->UpdateHealthBar(CurrentHealth);
	}
}

void UBuildingComponent::GetSuitableLocation(UGoalLocation*& SuitableLocationRef)
{
	TArray<UGoalLocation*> GoalLocations;
	GetOwner()->GetComponents<UGoalLocation>(GoalLocations);

	if (!GoalLocations.IsEmpty())
	{
		int32 RandomIndex = FMath::RandRange(0, GoalLocations.Num() - 1);
		GoalLocations[RandomIndex]->IsFull = true;
		SuitableLocationRef = GoalLocations[RandomIndex];
	}
}

// Called when the game starts
void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthBarWidgetComponent = Cast<UBaseHealthBarWidgetComponent>(GetOwner()->GetComponentByClass(UBaseHealthBarWidgetComponent::StaticClass()));
	HealthBarWidgetComponent->SetDrawSize(HealthBarDrawSize);
	UpdateHealthBar();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UBuildingComponent::OnOwnerTakeAnyDamage);
}

void UBuildingComponent::OnOwnerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	Health = UKismetMathLibrary::Max(Health, 0);
	UpdateHealthBar();

	if (Health <= 0)
	{
		OnBuildingDestroyed.Broadcast(TeamAttitude);
	}
}

// Called every frame
void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

