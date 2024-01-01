// Fill out your copyright notice in the Description page of Project Settings.

#include "Units/BaseUnits.h"
#include "BasePlayerController.h"
#include "Units/BaseUnitComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Units/BaseAIControllerUnits.h"

// Sets default values
ABaseUnits::ABaseUnits()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthBarWidgetComponent = CreateDefaultSubobject<UBaseHealthBarWidgetComponent>("HealthBarWidgetComponent");
	HealthBarWidgetComponent->SetupAttachment(GetCapsuleComponent());

	SelectionComponent = CreateDefaultSubobject<USelectComponent>("SelectionComponent");
	UnitComponent = CreateDefaultSubobject<UBaseUnitComponent>("UnitComponent");
}

// Called when the game starts or when spawned
void ABaseUnits::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UnitComponent->OnKillUnitDelegate.AddDynamic(this, &ABaseUnits::OnKillEnemy);

	AIControllerUnits = Cast<ABaseAIControllerUnits>(GetController());
}

void ABaseUnits::SetTeam_Implementation(uint8 const& id)
{
	TeamId = FGenericTeamId(id);
}

FGenericTeamId ABaseUnits::GetGenericTeamId_Implementation() const
{
	return TeamId;
}

void ABaseUnits::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	if (UnitComponent->TeamAttitude == ETeamAttitude::Friendly)
	{
		PlayerController->ClickSelectThisActor(this);
	}
}

// Called every frame
void ABaseUnits::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseUnits::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseUnits::SelectThis()
{
	SelectionComponent->ShowSelectionDecal();
}

void ABaseUnits::DeselectThis()
{
	SelectionComponent->HideSelectionDecal();
}

void ABaseUnits::OnKillEnemy(TEnumAsByte<ETeamAttitude::Type> TeamAttitude)
{
	Destroy();
}
