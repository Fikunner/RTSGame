// Fill out your copyright notice in the Description page of Project Settings.

#include "Units/BaseWorker.h"
#include "AIController.h"
#include "Units/BaseAIControllerUnits.h"
#include "Kismet/KismetMathLibrary.h"
#include "Framework/BaseRTSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Delegates/DelegateCombinations.h"
#include "Resources/ResourceComponent.h"
#include "Components/CapsuleComponent.h"
#include "Units/BaseUnitComponent.h"
#include "HUD/UnitSelectionMarquee.h"

// Sets default values
ABaseWorker::ABaseWorker()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetectEnemiesCollisions = CreateDefaultSubobject<UBoxComponent>("DetectEnemies");
	DetectEnemiesCollisions->SetupAttachment(GetCapsuleComponent());
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

void ABaseWorker::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IUnitActions* UnitActions = Cast<IUnitActions>(OtherActor);

	if (OtherActor != this && OtherActor != GetOwner() && OtherActor->IsA(ABaseWorker::StaticClass()) && OtherActor->GetClass()->ImplementsInterface(UUnitActions::StaticClass())
		&& BaseUnitComponent->TeamAttitude == ETeamAttitude::Hostile && Execute_GetGenericTeamId(this) != UnitActions->Execute_GetGenericTeamId(OtherActor))
	{
		UnitActions->AttackThisActor(OtherActor);
	}
}

void ABaseWorker::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IUnitActions* UnitActions = Cast<IUnitActions>(OtherActor);

	if (OtherActor != this && OtherActor != GetOwner() && OtherActor->IsA(ABaseWorker::StaticClass()) && OtherActor->GetClass()->ImplementsInterface(UUnitActions::StaticClass())
		&& BaseUnitComponent->TeamAttitude == ETeamAttitude::Hostile && Execute_GetGenericTeamId(this) != UnitActions->Execute_GetGenericTeamId(OtherActor))
	{
		for (AActor* ArrayElements : RTSGameMode->ATownHalls)
		{
			UnitActions->AttackThisActor(OtherActor);
		}
	}
}

// Called when the game starts or when spawned
void ABaseWorker::BeginPlay()
{
	Super::BeginPlay();

	RTSGameMode = Cast<ABaseRTSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	//AIControllerUnits = Cast<ABaseAIControllerUnits>(GetController());

	//PathFollowingComponent = AIControllerUnits->GetPathFollowingComponent();

	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	BaseUnitComponent = Cast<UBaseUnitComponent>(GetComponentByClass(UBaseUnitComponent::StaticClass()));
	BaseUnitComponent->OnKillUnitDelegate.AddDynamic(this, &ABaseWorker::OnKillEnemy);

	HUD = Cast<ABaseHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	DetectEnemiesCollisions->OnComponentBeginOverlap.AddDynamic(this, &ABaseWorker::OnBeginOverlap);
	DetectEnemiesCollisions->OnComponentEndOverlap.AddDynamic(this, &ABaseWorker::OnEndOverlap);
}

void ABaseWorker::OnKillEnemy(TEnumAsByte<ETeamAttitude::Type> TeamAttitude)
{
	int x = 0;
	Destroy();
	HUD->HUDWidgetRef->UpdateNumberOfPlayerUnits(x);
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

void ABaseWorker::SetTimerWithDelegate(FTimerHandle& TimerHandle, TDelegate<void()> ObjectDelegate, float Time, bool bLoop)
{
	GetWorld()->GetTimerManager().ClearTimer(HandleGatherThisResource);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, ObjectDelegate, Time, bLoop);
}