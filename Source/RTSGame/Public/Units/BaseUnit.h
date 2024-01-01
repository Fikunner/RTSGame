// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Buildings/SelectionEvent.h"
#include "UnitActions.h"
#include "Navigation/PathFollowingComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseUnit.generated.h"

//UENUM(BlueprintType)
//enum class EUnitState : uint8
//{
//	None UMETA(DisplayName = "None"),
//	Idle UMETA(DisplayName = "Idle"),
//	Movement UMETA(DisplayName = "Movement"),
//	Mining UMETA(DisplayName = "Mining"),
//	Attacking UMETA(DisplayName = "Attacking")
//};

UCLASS()
class RTSGAME_API ABaseUnit : public ACharacter, public IUnitActions, public ISelectionEvent
{
	GENERATED_BODY()

public:
	
	ABaseUnit();


	UFUNCTION()
	void SetTeam_Implementation(uint8 const& id) override;
	UFUNCTION()
	FGenericTeamId GetGenericTeamId_Implementation() const override;
	
	UPROPERTY(EditAnywhere)
	FGenericTeamId TeamId;

	UPROPERTY(EditAnywhere)
	class UBaseHealthBarWidgetComponent* HealthBarWidgetComponent;

	virtual void SelectThis() override;

	virtual void DeselectThis() override;

protected:

	virtual void BeginPlay() override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBaseUnitComponent* BaseUnitComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USelectComponent* SelectionComponent;

	void OnMoveCompletedMoveUnitToThisLocation(FAIRequestID RequestID, const FPathFollowingResult& Result);

	UPathFollowingComponent* PathFollowingComponent;

	class ABaseAIControllerUnits* AIControllerUnits;

	class ABasePlayerController* PlayerController;

public:

	UFUNCTION()
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
