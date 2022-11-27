// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "Components/InputComponent.h"
#include "Buildings/SelectionEvent.h"
#include "Buildings/BaseBuildings.h"
#include "Units/BaseWorker.h"
#include "Units/BaseAIControllerUnits.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

ABasePlayerController::ABasePlayerController()
{
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis("MoveForward", this, &ABasePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABasePlayerController::MoveRight);
	InputComponent->BindAxis("MouseMovement", this, &ABasePlayerController::MouseMovement);

	InputComponent->BindAction("MouseSelection", IE_Pressed, this, &ABasePlayerController::MouseSelection);
	InputComponent->BindAction("MouseAction", IE_Released, this, &ABasePlayerController::MouseAction);
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
	
	const TArray<AActor*> ActorsToIgnore;

	UClass* ActorClassFilter = NULL;

	if (!SelectedActors.IsEmpty())
	{
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), HitLocation, 100.f, ObjectTypes, ActorClassFilter, ActorsToIgnore, OutActors);

		if (OutActors.IsEmpty())
		{
			for (AActor* ArrayElements : SelectedActors)
			{
				Worker = Cast<ABaseWorker>(ArrayElements);

				if (Worker)
				{
					//Worker->MoveUnitToThisLocation(HitLocation);
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_ClickIndicator, HitLocation);
				}
			}
		}

		else if (UKismetSystemLibrary::IsValid(OutActors[0]))
		{
			for (AActor* ArrayElements : SelectedActors)
			{
				Worker = Cast<ABaseWorker>(ArrayElements);

				if (Worker)
				{
					//Worker->GatherThisResource(OutActors[0]);
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
}

void ABasePlayerController::DeselectAllActors_Implementation()
{
	for (AActor* ArrayElements : SelectedActors)
	{
		BuildingBase = Cast<ABaseBuildings>(ArrayElements);

		if (BuildingBase)
		{
			BuildingBase->DeselectThisActor();
		}
		
	}

	SelectedActors.Empty();
}

void ABasePlayerController::AddActorSelectedToList_Implementation(AActor* SelectedActor)
{
	DeselectAllActors_Implementation();

	SelectedActors.Add(SelectedActor);
}
