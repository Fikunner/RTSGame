// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "Components/InputComponent.h"
#include "Buildings/BaseBuildings.h"
#include "Units/BaseWorker.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HUD/BaseHUD.h"
#include "HUD/BaseUserWidgetHUD.h"
#include "HUD/UnitSelectionMarquee.h"

ABasePlayerController::ABasePlayerController()
{
}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis("MoveForward", this, &ABasePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABasePlayerController::MoveRight);
	InputComponent->BindAxis("MouseMovement", this, &ABasePlayerController::MouseMovement);

	InputComponent->BindAction("MouseSelection", IE_Pressed, this, &ABasePlayerController::MouseSelection);
	InputComponent->BindAction("MouseSelection", IE_Released, this, &ABasePlayerController::MouseDeselection);

	InputComponent->BindAction("MouseAction", IE_Released, this, &ABasePlayerController::MouseAction);
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	FVector Location(0.f, 0.f, 0.f);
	FRotator Rotation(0.f, 0.f, 0.f);
	FActorSpawnParameters SpawnInfo;

	SelectionMarqueeRef = GetWorld()->SpawnActor<AUnitSelectionMarquee>(UnitSelectionMarqueeToSpawn, Location, Rotation, SpawnInfo);
}

void ABasePlayerController::MoveForward(float Value)
{
	const FRotator Rotation = ControlRotation;
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	GetPawn()->AddMovementInput(Direction, UKismetMathLibrary::SelectFloat(Value, MouseForwardScale, Value != 0));
}

void ABasePlayerController::MoveRight(float Value)
{
	const FRotator Rotation = ControlRotation;
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(Direction, UKismetMathLibrary::SelectFloat(Value, MouseRightScale, Value != 0));
}

void ABasePlayerController::MouseMovement(float Value)
{

}

void ABasePlayerController::MouseSelection()
{
	FVector HitLocation = FVector::ZeroVector;
	FHitResult Hit;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, Hit);
	HitLocation = Hit.Location;

	SelectionMarqueeRef->SetActorLocation(HitLocation);

	SelectionMarqueeRef->ShouldResizeMarquee = true;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Select");
}

void ABasePlayerController::MouseDeselection()
{
	SelectionMarqueeRef->ShouldResizeMarquee = false;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, "Deselect");
}

void ABasePlayerController::MouseAction()
{
	FVector HitLocation = FVector::ZeroVector;
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	HitLocation = Hit.Location;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	if (!SelectedActors.IsEmpty())
	{
		const TArray<AActor*> ActorsToIgnore;
		UClass* ActorClassFilter = nullptr;
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), HitLocation, 100.f, ObjectTypes, ActorClassFilter, ActorsToIgnore, OutActors);

		if (OutActors.IsEmpty())
		{
			for (AActor* ArrayElements : SelectedActors)
			{
				IUnitActions* UnitActions = Cast<IUnitActions>(ArrayElements);
				if (UnitActions)
				{
					UnitActions->Execute_MoveUnitToThisLocation(ArrayElements, HitLocation);
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_ClickIndicator, HitLocation);
				}
			}
		}

		else
		{
			for (AActor* ArrayElements : SelectedActors) 
			{
				IUnitActions* UnitActions = Cast<IUnitActions>(ArrayElements);
				if (UnitActions)
				{
					if (IsValid(OutActors[0]->GetComponentByClass(ResourceComp)))
					{
						UnitActions->Execute_GatherThisResource(ArrayElements, OutActors[0]);
					}
					if (IsValid(OutActors[0]->GetComponentByClass(BuildingComp)))
					{
						UnitActions->Execute_InteractWithBuilding(ArrayElements, OutActors[0]);
					}
				}
			}
		}
	}
}

void ABasePlayerController::ReceiveResources(EResourceTypes ResourceType, int32 Amount)
{
	if (StoredResource.Contains(ResourceType))
	{
		Amount += *StoredResource.Find(ResourceType);

		StoredResource.Add(ResourceType, Amount);
	}

	else
	{
		StoredResource.Add(ResourceType, Amount);
	}

	HUD = Cast<ABaseHUD>(GetHUD());

	HUD->HUDWidgetRef->UpdateResourceValue(ResourceType, *StoredResource.Find(ResourceType));
}

void ABasePlayerController::DeselectAllActors()
{
	for (AActor* ArrayElements : SelectedActors)
	{
		ISelectionEvent* SelectionEvent = Cast<ISelectionEvent>(ArrayElements);
		if (SelectionEvent)
		{
			SelectionEvent->DeselectThisActor();
		}

		//6:17:00
	}

	SelectedActors.Empty();
}

void ABasePlayerController::AddActorSelectedToList_Implementation(AActor* SelectedActor)
{
	DeselectAllActors();

	SelectedActors.Add(SelectedActor);
}
