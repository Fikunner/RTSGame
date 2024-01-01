// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimMontage.h"
#include "Units/BaseUnitComponent.h"
#include "CoreMinimal.h"
#include "Units/BaseUnits.h"
#include "BaseWarriors.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ABaseWarriors : public ABaseUnits
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MoveUnitToThisLocation(FVector Location);

	void ActorAttackTownHall(FVector Destination);
	void ActorAttackUnit(AActor* TargetActor);

	virtual void AttackThisActor(AActor* ActorToAttack) override;

protected:

	virtual void BeginPlay() override;

	void OnMoveCompletedMoveUnitToThisLocation(FAIRequestID RequestID, const FPathFollowingResult& Result);

	void OnMoveCompletedToAttackedActor(FAIRequestID RequestID, const FPathFollowingResult& Result);

	void Attack();
	void StopAttacking();

	void ComboAttackAnimations();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TArray<UAnimMontage*> AnimationsCombo;

	double RangeToActorToAttack;

	AActor* UnitToAttack;

	FTimerHandle AttackTimer;

	class ABaseAIControllerUnits* AIControllerUnits;
	class UBaseUnitComponent* UnitComponent;

private:

	FVector GetTownHallDestination();

	class UBuildingComponent* BuildingComponent;

	int CurrentAnimIndex;

};
