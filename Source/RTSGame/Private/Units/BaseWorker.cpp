// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/BaseWorker.h"
#include "Components/DecalComponent.h"
#include "AIController.h"
#include "Units/BaseAIControllerUnits.h"
#include "Kismet/KismetMathLibrary.h"
#include "Framework/BaseRTSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BasePlayerController.h"
#include "Delegates/DelegateCombinations.h"
#include "GameFramework/PlayerController.h"
#include "Resources/ResourceComponent.h"
#include "Components/CapsuleComponent.h"
#include "Units/BaseUnitComponent.h"

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

	if (BaseUnitComponent->TeamAttitude == ETeamAttitude::Friendly)
	{
		Decal->SetVisibility(true, false);
		Decal->SetHiddenInGame(false, false);

		PlayerController->ClickSelectThisActor(this);
	}
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

	BaseUnitComponent->OnEnterNewStateDelegate.AddDynamic(this, &ABaseWorker::OnEnterNewState);
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

void ABaseWorker::OnEnterNewState(EUnitState NewUnitState)
{
	switch (NewUnitState)
	{
		case EUnitState::Idle:

			GetMesh()->PlayAnimation(AnimationIdle, true);
			break;

		case EUnitState::Movement:
			
			GetMesh()->PlayAnimation(AnimationOfWalkFWD, true);
			break;

		case EUnitState::Mining:

			GetMesh()->PlayAnimation(AnimMontageMining, true);
			break;

		case EUnitState::Attacking:

			GetMesh()->PlayAnimation(AnimationOfAttacking, true);
			break;
	}
}
