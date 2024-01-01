// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/BaseWarriors.h"
#include "Units/BaseAIControllerUnits.h"
#include "Buildings/BuildingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void ABaseWarriors::BeginPlay()
{
	Super::BeginPlay();

	AIControllerUnits = ABaseUnits::AIControllerUnits;
	UnitComponent = ABaseUnits::UnitComponent;
}

void ABaseWarriors::MoveUnitToThisLocation_Implementation(FVector Location)
{
	AIControllerUnits->GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);
	AIControllerUnits->MoveToLocation(Location);
	AIControllerUnits->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ABaseWarriors::OnMoveCompletedMoveUnitToThisLocation);
}

void ABaseWarriors::ActorAttackTownHall(FVector Destination)
{
	AIControllerUnits->GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);
	AIControllerUnits->MoveToLocation(Destination, 50.f, true);
	AIControllerUnits->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ABaseWarriors::OnMoveCompletedToAttackedActor);
}

void ABaseWarriors::ActorAttackUnit(AActor* TargetActor)
{
	AIControllerUnits->GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);
	AIControllerUnits->MoveToActor(TargetActor, 200.f, true);
	AIControllerUnits->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ABaseWarriors::OnMoveCompletedToAttackedActor);
}

void ABaseWarriors::AttackThisActor(AActor* ActorToAttack)
{
	if (IsValid(ActorToAttack))
	{
		UnitToAttack = ActorToAttack;

		BuildingComponent = Cast<UBuildingComponent>(UnitToAttack->GetComponentByClass(UBuildingComponent::StaticClass()));

		AIControllerUnits = Cast<ABaseAIControllerUnits>(GetController());

		if (IsValid(BuildingComponent))
		{
			ActorAttackTownHall(GetTownHallDestination());
		}
		
		else
		{
			ActorAttackUnit(UnitToAttack);
		}

	}
}

void ABaseWarriors::OnMoveCompletedToAttackedActor(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (IsValid(UnitToAttack))
	{
		RangeToActorToAttack = FVector::Distance(UnitToAttack->GetActorLocation(), GetActorLocation());

		FRotator Rotation = FRotator(0, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UnitToAttack->GetActorLocation()).Yaw, 0);

		SetActorRotation(Rotation);

		GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &ABaseWarriors::Attack, 1.f, true);
	}

	else
	{
		StopAttacking();
	}
}

void ABaseWarriors::Attack()
{
	if (IsValid(UnitToAttack))
	{
		double Distance = FVector::Distance(UnitToAttack->GetActorLocation(), GetActorLocation());
		if (Distance <= RangeToActorToAttack)
		{
			AController* EventInstigator = nullptr;
			AActor* DamageCauser = nullptr;
			TSubclassOf<UDamageType> DamageTypeClass;

			ComboAttackAnimations();

			UGameplayStatics::ApplyDamage(UnitToAttack, UnitComponent->DamageToApply, EventInstigator, DamageCauser, DamageTypeClass);
		}

		else
		{
			StopAttacking();

			if (UnitComponent->StateOfUnit == EUnitState::Attacking && IsValid(UnitToAttack))
			{
				AttackThisActor(UnitToAttack);
			}
		}
	}

	else
	{
		StopAttacking();
	}
}

void ABaseWarriors::StopAttacking()
{
	CurrentAnimIndex = 0;

	GetWorldTimerManager().ClearTimer(AttackTimer);
}

void ABaseWarriors::ComboAttackAnimations()
{
	CurrentAnimIndex += 1;

	switch (CurrentAnimIndex)
	{
		case 1:
		{
			PlayAnimMontage(AnimationsCombo[0]);

			break;
		}

		case 2:
		{
			PlayAnimMontage(AnimationsCombo[1]);

			break;
		}

		case 3:
		{
			PlayAnimMontage(AnimationsCombo[2]);

			CurrentAnimIndex = 0;
			break;
		}
	}
	

}

FVector ABaseWarriors::GetTownHallDestination()
{
	UGoalLocation* GoalLoc;
	BuildingComponent->GetSuitableLocation(GoalLoc);
	FVector Destination = GoalLoc->GetComponentLocation();

	return Destination;
}

void ABaseWarriors::OnMoveCompletedMoveUnitToThisLocation(FAIRequestID RequestID, const FPathFollowingResult& Result)
{

}
