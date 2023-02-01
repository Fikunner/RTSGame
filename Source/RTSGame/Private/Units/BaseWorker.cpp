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
}


void ABaseWorker::MoveUnitToThisLocation_Implementation(FVector Location)
{
	/*BaseUnitComponent->HandleNewUnitState(EUnitState::Movement);

	AIControllerUnits->MoveToLocation(Location, 50.f);

	if (AIControllerUnits)
	{
		PathFollowingComponent->OnRequestFinished.AddUObject(this, &ABaseWorker::OnMoveCompletedMoveUnitToThisLocation);
	}*/
}

void ABaseWorker::OnMoveCompletedMoveUnitToThisLocation(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	/*if (Result.Code == EPathFollowingResult::Success || Result.Code == EPathFollowingResult::Blocked || Result.Code == EPathFollowingResult::OffPath || Result.Code == EPathFollowingResult::Invalid)
	{
		BaseUnitComponent->HandleNewUnitState(EUnitState::Idle);
	}

	PathFollowingComponent->OnRequestFinished.RemoveAll(this);*/
}

void ABaseWorker::GatherThisResource_Implementation(AActor* ResourceRef)
{	
	/*if (AIControllerUnits)
	{
		PathFollowingComponent->OnRequestFinished.RemoveAll(this);
		PathFollowingComponent->OnRequestFinished.AddUObject(this, &ABaseWorker::OnMoveCompletedGatherThisResource);
	}
	
	BaseUnitComponent->HandleNewUnitState(EUnitState::Movement);

	ResourcePosition = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResourceRef->GetActorLocation());

	AIControllerUnits->MoveToActor(ResourceRef, 200.f);*/
}

void ABaseWorker::OnMoveCompletedGatherThisResource(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	/*if (Result.Code == EPathFollowingResult::Success)
	{
		DelegateGatherThisResource.BindLambda([&]()
		{
			if (BaseUnitComponent->UnitState == EUnitState::Mining)
			{
				ResourceComponent->GiveResource(ResourceBeingCarried, AmountOfResources);

				GoToTownHallAndDepositResources(RTSGameMode->GetPlayerTownHall());
			}
		});

		SetActorRotation(FRotator(0, ResourcePosition.Yaw, 0));

		if (ResourceComponent->CanThisResourceBeMined() && ResourceBeingCarried != ResourceComponent->TypeOfResource)
		{
			BaseUnitComponent->HandleNewUnitState(EUnitState::Mining);
			SetTimerWithDelegate(HandleGatherThisResource, DelegateGatherThisResource, ResourceComponent->TimeItTakesToBeGatheredInSeconds, false);
			
		}

		else
		{
			if (ResourceBeingCarried == ResourceComponent->TypeOfResource && AmountOfResources > 0)
			{
				GoToTownHallAndDepositResources(RTSGameMode->GetPlayerTownHall());
			}
			else
			{
				BaseUnitComponent->HandleNewUnitState(EUnitState::Idle);
			}
		}
	}*/
}

void ABaseWorker::InteractWithBuilding_Implementation(AActor* BuildingRef)
{
	//if (UKismetSystemLibrary::IsValid(BuildingRef->FindComponentByClass<UBuildingComponent>()))
	//{
	//	if (AmountOfResources > 0 && BuildingRef->FindComponentByClass<UBuildingComponent>()->TypeOfBuilding == EBuildingTypes::TownHall)
	//	{
	//		GoToTownHallAndDepositResources(RTSGameMode->GetPlayerTownHall());
	//	}
	//	else
	//	{
	//		//TODO: Here we should repair the building if need to repair;
	//	}
	//}

	//else
	//{

	//}
}

void ABaseWorker::GoToTownHallAndDepositResources_Implementation(AActor* ResourceRef)
{
	/*if (AIControllerUnits)
	{
		PathFollowingComponent->OnRequestFinished.AddUObject(this, &ABaseWorker::OnMoveCompletedGoToTownHallAndDepositResources);
	}
	
	BaseUnitComponent->HandleNewUnitState(EUnitState::Movement);

	AIControllerUnits->MoveToActor(ResourceRef, 200.f, true);*/
}

void ABaseWorker::OnMoveCompletedGoToTownHallAndDepositResources(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	/*if (Result.Code == EPathFollowingResult::Success)
	{
		BaseUnitComponent->HandleNewUnitState(EUnitState::Idle);
		PlayerController->ReceiveResources(ResourceBeingCarried, AmountOfResources);
		
		ResourceBeingCarried = EResourceTypes::None;
		AmountOfResources = 0;

		if (ResourceComponent->CanThisResourceBeMined())
		{
			GatherThisResource(PlayerController->OutActors[0]);
			PlayerController->OutActors.IsEmpty();
		}
	}*/
}

void ABaseWorker::RepeatTheMiningAction_Implementation(AActor* ResourceRef)
{
}

// Called when the game starts or when spawned
void ABaseWorker::BeginPlay()
{
	Super::BeginPlay();
	
	//TArray<UResourceComponent*> ResourceComps;

	//GetComponents(ResourceComps);
	//if (ResourceComps.Num() > 0)
	//{
	//	ResourceComponent = ResourceComps[0];
	//}
	
	/*if (ResourceComponent == nullptr)
	{
		ResourceComponent = NewObject<UResourceComponent>();
	}*/

	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	RTSGameMode = Cast<ABaseRTSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	AIControllerUnits = Cast<ABaseAIControllerUnits>(GetController());
	
	PathFollowingComponent = AIControllerUnits->GetPathFollowingComponent();
	
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
