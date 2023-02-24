// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/BaseUnitComponent.h"
#include "BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"
#include "Components/DecalComponent.h"

// Sets default values for this component's properties
UBaseUnitComponent::UBaseUnitComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Health = HealthMax;

}

// Called when the game starts
void UBaseUnitComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthBarWidgetComponent = Cast<UBaseHealthBarWidgetComponent>(GetOwner()->GetComponentByClass(UBaseHealthBarWidgetComponent::StaticClass()));

	UpdateHealthBar();

	GetOwner()->OnClicked.AddDynamic(this, &UBaseUnitComponent::OnOwnerClicked);
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UBaseUnitComponent::OnOwnerTakeAnyDamage);
}

void UBaseUnitComponent::OnOwnerClicked_Implementation(AActor* TouchedActor, FKey ButtonPressed)
{
	AddUnitToSelectionList();
	ShowSelectionDecal();
}

void UBaseUnitComponent::OnOwnerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	Health = UKismetMathLibrary::Max(Health, 0);
	UpdateHealthBar();
}

void UBaseUnitComponent::AddUnitToSelectionList_Implementation()
{
	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->AddActorSelectedToList(GetOwner());
}

void UBaseUnitComponent::ShowSelectionDecal_Implementation()
{		
	TArray<UDecalComponent*> DecalsComp;
	
	GetOwner()->GetComponents(DecalsComp);
	if (DecalsComp.Num() > 0)
	{
		UDecalComponent* FoundDecal = DecalsComp[0];

		FoundDecal->SetVisibility(true, false);
		FoundDecal->SetHiddenInGame(false, false);
	}
}

void UBaseUnitComponent::HideSelectionDecal_Implementation()
{
	TArray<UDecalComponent*> DecalsComp;

	GetOwner()->GetComponents(DecalsComp);
	if (DecalsComp.Num() > 0)
	{
		UDecalComponent* FoundDecal = DecalsComp[0];

		FoundDecal->SetVisibility(false, false);
		FoundDecal->SetHiddenInGame(true, false);
	}
}

void UBaseUnitComponent::HandleNewUnitState(EUnitState NewUnitState)
{
	StateOfUnit = NewUnitState;

	switch (NewUnitState)
	{
	case EUnitState::Idle:
		
		OnEnterIdleDelegate.Broadcast();

		break;
	case EUnitState::Movement:

		OnEnterMovementDelegate.Broadcast();

		break;
	case EUnitState::Mining:

		OnEnterMiningDelegate.Broadcast();

		break;

	default:

		break;
	}
}

// Called every frame
void UBaseUnitComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UBaseUnitComponent::UpdateHealthBar()
{
	float CurrentHealth = Health / HealthMax;

	if (IsValid(HealthBarWidgetComponent))
	{
		HealthBarWidgetComponent->SetDrawSize(FVector2D(50,8));
		HealthBarWidgetComponent->UpdateHealthBar(CurrentHealth);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "UnitComponent: No Healthbar component valid");
	}
}
