// Fill out your copyright notice in the Description page of Project Settings.

#include "Buildings/BaseBuildings.h"
#include "BasePlayerController.h"
#include "Kismet/Gameplaystatics.h"
#include "Buildings/BuildingComponent.h"
#include "Units/SelectionComponent.h"

// Sets default values
ABaseBuildings::ABaseBuildings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	Mesh->SetupAttachment(RootComponent);

	HealthBarWidgetComponent = CreateDefaultSubobject<UBaseHealthBarWidgetComponent>("HealthBarWidgetComponent");
	HealthBarWidgetComponent->SetupAttachment(Mesh);
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComponent->SetDrawSize(FVector2D(200, 20));

	BuildingComponent = CreateDefaultSubobject<UBuildingComponent>("BuildingComponent");
	SelectionComponent = CreateDefaultSubobject<USelectionComponent>("SelectionComponent");
}

void ABaseBuildings::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	BuildingClicked_Implementation();

}

void ABaseBuildings::BuildingClicked_Implementation()
{
	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->AddActorSelectedToList(this);

	SelectionComponent->ShowSelectionDecal();
}

void ABaseBuildings::SelectThis()
{
	SelectionComponent->ShowSelectionDecal();
}

void ABaseBuildings::DeselectThis()
{
	SelectionComponent->HideSelectionDecal();
}

void ABaseBuildings::OnBuildingDestroyed(TEnumAsByte<ETeamAttitude::Type> TeamAttitude)
{
	Destroy();
}

// Called when the game starts or when spawned
void ABaseBuildings::BeginPlay()
{
	Super::BeginPlay();

	BuildingComponent->OnBuildingDestroyed.AddDynamic(this, &ABaseBuildings::OnBuildingDestroyed);

}

// Called every frame
void ABaseBuildings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

