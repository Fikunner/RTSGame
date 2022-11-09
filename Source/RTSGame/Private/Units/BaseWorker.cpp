// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/BaseWorker.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "Units/BaseAIControllerUnits.h"
#include "NavigationSystem.h"
#include "AITypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "Units/BaseUnitComponent.h"
#include "Framework/BaseRTSGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseWorker::ABaseWorker()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Decal = CreateDefaultSubobject<UDecalComponent>("DecalComponent");
	Decal->SetupAttachment(GetMesh());
	
	BaseUnitComponent = CreateDefaultSubobject<UBaseUnitComponent>("BaseUnitComponent");

}

void ABaseWorker::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	Decal->SetVisibility(true, false);
	Decal->SetHiddenInGame(false, false);

	GEngine->AddOnScreenDebugMessage(-1, 5.f , FColor::Red, "Clicked Actor");
}

void ABaseWorker::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "OnMoveCompleted always");
	
	bool GoToTownHall = false;

	if (bMoveUnitToThisLocation && Result.Code == EPathFollowingResult::Success || Result.Code == EPathFollowingResult::Blocked || Result.Code == EPathFollowingResult::OffPath || Result.Code == EPathFollowingResult::Invalid)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "OnMoveCompleted in MoveUnitToThisLocation");

		bMoveUnitToThisLocation = false;

		BaseUnitComponent->HandleNewUnitState(EUnitState::Idle);
	}

	if (bGatherThisResource && Result.Code == EPathFollowingResult::Success)
	{	
		DelegateGatherThisResource.BindLambda([&]()
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "OnMoveCompleted in GatherThisResource");
			if (BaseUnitComponent->UnitState == EUnitState::Mining)
			{
				ResourceBeingCarried = ResourceComponent->TypeOfResource;
				AmountOfResources = ResourceComponent->NumberOfResourcesToGive;

				RTSGameMode = Cast<ABaseRTSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

				BaseUnitComponent->HandleNewUnitState(EUnitState::Movement);

				AIControllerUnits->MoveToActor(RTSGameMode->GetPlayerTownHall(RTSGameMode->TownHallLoc), 200.f, true);

				GoToTownHall = true;
			}
		});

		bGatherThisResource = false;
		SetActorRotation(FRotator(0, ResourcePosition.Yaw, 0));

		if (ResourceBeingCarried != ResourceComponent->TypeOfResource)
		{
			BaseUnitComponent->HandleNewUnitState(EUnitState::Mining);
			
			AmountOfResources = 0;
			
			SetTimerWithDelegate(HandleGatherThisResource, DelegateGatherThisResource, ResourceComponent->TimeItTakesToBeGatheredInSeconds, false);
		}
		else
		{
			BaseUnitComponent->HandleNewUnitState(EUnitState::Idle);
		}
	}

	if (GoToTownHall)
	{
		GoToTownHall = false;

		BaseUnitComponent->HandleNewUnitState(EUnitState::Idle);
	}
}

void ABaseWorker::SetTimerWithDelegate(FTimerHandle& TimerHandle, TBaseDelegate<void> ObjectDelegate, float Time, bool bLoop)
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

void ABaseWorker::MoveUnitToThisLocation(FVector Location)
{	
	BaseUnitComponent->HandleNewUnitState(EUnitState::Movement);

	bMoveUnitToThisLocation = true;
	AIControllerUnits->MoveToLocation(Location, 50.f);
}

void ABaseWorker::GatherThisResource(AActor* ResourceRef)
{	
	BaseUnitComponent->HandleNewUnitState(EUnitState::Movement);
	
	ResourcePosition = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResourceRef->GetActorLocation());

	bGatherThisResource = true;
	AIControllerUnits->MoveToActor(ResourceRef, 200.f);
}

// Called when the game starts or when spawned
void ABaseWorker::BeginPlay()
{
	Super::BeginPlay();

	if (ResourceComponent == NULL)
	{
		ResourceComponent = NewObject<UResourceComponent>(this);
	}

	AIControllerUnits = Cast<ABaseAIControllerUnits>(GetController());

	PathFollowingComponent = AIControllerUnits->GetPathFollowingComponent();

	if (AIControllerUnits)
	{
		PathFollowingComponent->OnRequestFinished.AddUObject(this, &ABaseWorker::OnMoveCompleted);
	}

	BaseUnitComponent = Cast<UBaseUnitComponent>(GetComponentByClass(UBaseUnitComponent::StaticClass()));

	BaseUnitComponent->OnEnterIdleDelegate.AddDynamic(this, &ABaseWorker::OnEnterIdle);
	BaseUnitComponent->OnEnterMovementDelegate.AddDynamic(this, &ABaseWorker::OnEnterMovement);
	BaseUnitComponent->OnEnterMiningDelegate.AddDynamic(this, &ABaseWorker::OnEnterMining);

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

