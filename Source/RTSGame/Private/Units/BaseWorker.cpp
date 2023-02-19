// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/BaseWorker.h"
#include "Components/DecalComponent.h"
#include "AIController.h"
#include "Units/BaseAIControllerUnits.h"
#include "Kismet/KismetMathLibrary.h"
#include "Units/BaseUnitComponent.h"
#include "Framework/BaseRTSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BasePlayerController.h"
#include "Delegates/DelegateCombinations.h"
#include "GameFramework/PlayerController.h"
#include "Resources/ResourceComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseWorker::ABaseWorker()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Decal = CreateDefaultSubobject<UDecalComponent>("DecalComponent");
	Decal->SetupAttachment(GetMesh());
	
	HealthBarWidgetComponent = CreateDefaultSubobject<UBaseHealthBarWidgetComponent>("HealthBarWidgetComponent");
	HealthBarWidgetComponent->SetupAttachment(GetCapsuleComponent());

	BaseUnitComponent = CreateDefaultSubobject<UBaseUnitComponent>("BaseUnitComponent");
}

void ABaseWorker::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	Decal->SetVisibility(true, false);
	Decal->SetHiddenInGame(false, false);

	PlayerController->ClickSelectThisActor(this);
}

void ABaseWorker::MoveUnitToThisLocation_Implementation(FVector Location)
{
	
}

void ABaseWorker::OnMoveCompletedMoveUnitToThisLocation(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	
}

void ABaseWorker::GatherThisResource_Implementation(AActor* ResourceRef)
{	
	
}

void ABaseWorker::OnMoveCompletedGatherThisResource(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	
}

void ABaseWorker::InteractWithBuilding_Implementation(AActor* BuildingRef)
{
	
}

void ABaseWorker::GoToTownHallAndDepositResources_Implementation(AActor* ResourceRef)
{
	
}

void ABaseWorker::OnMoveCompletedGoToTownHallAndDepositResources(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	
}

void ABaseWorker::RepeatTheMiningAction_Implementation(AActor* ResourceRef)
{
}

void ABaseWorker::SelectThis()
{	
	if (BaseUnitComponent)
	{
		BaseUnitComponent->ShowSelectionDecal();
	}
}

void ABaseWorker::DeselectThis()
{
	if (BaseUnitComponent)
	{
		BaseUnitComponent->HideSelectionDecal();
	}
}

// Called when the game starts or when spawned
void ABaseWorker::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	RTSGameMode = Cast<ABaseRTSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	AIControllerUnits = Cast<ABaseAIControllerUnits>(GetController());
	
	PathFollowingComponent = AIControllerUnits->GetPathFollowingComponent();
	
	BaseUnitComponent = Cast<UBaseUnitComponent>(GetComponentByClass(UBaseUnitComponent::StaticClass()));
	
	BaseUnitComponent->OnEnterIdleDelegate.AddDynamic(this, &ABaseWorker::OnEnterIdle);
	BaseUnitComponent->OnEnterMovementDelegate.AddDynamic(this, &ABaseWorker::OnEnterMovement);
	BaseUnitComponent->OnEnterMiningDelegate.AddDynamic(this, &ABaseWorker::OnEnterMining);

	AController* controller = nullptr;
	AActor* damagecauser = nullptr;
	TSubclassOf<UDamageType> damagetype;

	UGameplayStatics::ApplyDamage(this, 20.f, controller, damagecauser, damagetype);

}

// Called every frame
void ABaseWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseWorker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseWorker::SetTimerWithDelegate(FTimerHandle& TimerHandle, TBaseDelegate<void>(ObjectDelegate), float Time, bool bLoop)
{
	GetWorld()->GetTimerManager().ClearTimer(HandleGatherThisResource);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, ObjectDelegate, Time, bLoop);
}

void ABaseWorker::OnEnterIdle()
{
	GetMesh()->PlayAnimation(AnimationIdle, true);
}

void ABaseWorker::OnEnterMovement()
{
	GetMesh()->PlayAnimation(AnimationOfWalkFWD, true);
}

void ABaseWorker::OnEnterMining()
{
	GetMesh()->PlayAnimation(AnimMontageMining, true);
}
