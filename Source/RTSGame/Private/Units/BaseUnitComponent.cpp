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

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, "TEST");

	UpdateHealthBar();

	GetOwner()->OnClicked.AddDynamic(this, &UBaseUnitComponent::OnOwnerClicked);
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UBaseUnitComponent::OnOwnerTakeAnyDamage);
}

void UBaseUnitComponent::OnOwnerClicked_Implementation(AActor* TouchedActor, FKey ButtonPressed)
{
	if (TeamAttitude == ETeamAttitude::Friendly)
	{
		AddUnitToSelectionList();
	}
}

void UBaseUnitComponent::OnOwnerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	Health = UKismetMathLibrary::Max(Health, 0);
	UpdateHealthBar();

	if (Health <= 0)
	{
		OnKillUnitDelegate.Broadcast(TeamAttitude);
	}
}

void UBaseUnitComponent::AddUnitToSelectionList_Implementation()
{
	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->AddActorSelectedToList(GetOwner());
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
		switch (TeamAttitude)
		{
		case ETeamAttitude::Friendly:

			HealthBarWidgetComponent->UpdateHealtBarColor(FriendlyColor);

			break;

		case ETeamAttitude::Neutral:

			HealthBarWidgetComponent->UpdateHealtBarColor(NeutralColor);

			break;
		case ETeamAttitude::Hostile:

			HealthBarWidgetComponent->UpdateHealtBarColor(HostileColor);

			break;
		
		default:

			break;
		}

		HealthBarWidgetComponent->SetDrawSize(FVector2D(50,8));
		HealthBarWidgetComponent->UpdateHealthBar(CurrentHealth);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "UnitComponent: No Healthbar component valid");
	}
}
