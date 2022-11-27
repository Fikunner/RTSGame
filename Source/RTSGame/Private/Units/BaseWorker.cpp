// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/BaseWorker.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "Units/BaseAIControllerUnits.h"
#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Units/BaseUnitComponent.h"
#include "Framework/BaseRTSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayerController.h"
#include "GameFramework/PlayerController.h"

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

/*
void ABaseWorker::MoveUnitToThisLocation(FVector Location)
{
	BaseUnitComponent->HandleNewUnitState(EUnitState::Movement);

	AIControllerUnits->MoveToLocation(Location, 50.f);

	if (AIControllerUnits)
	{
		PathFollowingComponent->OnRequestFinished.AddUObject(this, &ABaseWorker::OnMoveCompletedMoveUnitToThisLocation);
	}
}

void ABaseWorker::OnMoveCompletedMoveUnitToThisLocation(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.Code == EPathFollowingResult::Success || Result.Code == EPathFollowingResult::Blocked || Result.Code == EPathFollowingResult::OffPath || Result.Code == EPathFollowingResult::Invalid)
	{
		BaseUnitComponent->HandleNewUnitState(EUnitState::Idle);
	}

	PathFollowingComponent->OnRequestFinished.RemoveAll(this);
}

void ABaseWorker::GatherThisResource(AActor* ResourceRef)
{
	if (AIControllerUnits)
	{
		PathFollowingComponent->OnRequestFinished.RemoveAll(this);
		PathFollowingComponent->OnRequestFinished.AddUObject(this, &ABaseWorker::OnMoveCompletedGatherThisResource);
	}

	BaseUnitComponent->HandleNewUnitState(EUnitState::Movement);

	ResourcePosition = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResourceRef->GetActorLocation());

	AIControllerUnits->MoveToActor(ResourceRef, 200.f);
}

void ABaseWorker::OnMoveCompletedGatherThisResource(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, "OnMoveCompletedGatheredThisResource");

	if (Result.Code == EPathFollowingResult::Success)
	{
		DelegateGatherThisResource.BindLambda([&]()
		{
			if (BaseUnitComponent->UnitState == EUnitState::Mining)
			{
				ResourceBeingCarried = ResourceComponent->TypeOfResource;
				AmountOfResources = ResourceComponent->NumberOfResourcesToGive;
		
				BaseUnitComponent->HandleNewUnitState(EUnitState::Movement);

				AIControllerUnits->MoveToActor(RTSGameMode->GetPlayerTownHall(), 200.f, true);
			}
		});

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

			PlayerController->ReceiveResources(ResourceBeingCarried, AmountOfResources);

			ResourceBeingCarried = EResourceTypes::None;
			AmountOfResources = 0;

			GatherThisResource(PlayerController->OutActors[0]);

			PathFollowingComponent->OnRequestFinished.RemoveAll(this);
		}
	}
}
*/
// Called when the game starts or when spawned
void ABaseWorker::BeginPlay()
{
	Super::BeginPlay();

	ResourceComponent = NewObject<UResourceComponent>(this);

	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	RTSGameMode = Cast<ABaseRTSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	//AIControllerUnits = Cast<ABaseAIControllerUnits>(GetController());

	//PathFollowingComponent = AIControllerUnits->GetPathFollowingComponent();

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

//void ABaseWorker::SetTimerWithDelegate(FTimerHandle& TimerHandle, TBaseDelegate<void> ObjectDelegate, float Time, bool bLoop)
//{
//	GetWorld()->GetTimerManager().ClearTimer(HandleGatherThisResource);
//	GetWorld()->GetTimerManager().SetTimer(TimerHandle, ObjectDelegate, Time, bLoop);
//}

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
