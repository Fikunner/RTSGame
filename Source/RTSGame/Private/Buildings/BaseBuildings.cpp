// Fill out your copyright notice in the Description page of Project Settings.

#include "Buildings/BaseBuildings.h"
#include "BasePlayerController.h"
#include "Components/DecalComponent.h"
#include "Kismet/Gameplaystatics.h"

// Sets default values
ABaseBuildings::ABaseBuildings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	Mesh->SetupAttachment(RootComponent);

	Decal = CreateDefaultSubobject<UDecalComponent>("DecalComponent");
	Decal->SetupAttachment(Mesh);

	//BuildingComponent = CreateDefaultSubobject<UBuildingComponent>("BuildingComponent");

}

void ABaseBuildings::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	BuildingClicked_Implementation();
}

void ABaseBuildings::BuildingClicked_Implementation()
{
	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	BasePlayerController->AddActorSelectedToList_Implementation(this);

	Decal->SetHiddenInGame(false, false);
	Decal->SetVisibility(true, false);
}

void ABaseBuildings::DeselectThis()
{
	Decal->SetHiddenInGame(true, false);
	Decal->SetVisibility(false, false);
}

// Called when the game starts or when spawned
void ABaseBuildings::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseBuildings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

