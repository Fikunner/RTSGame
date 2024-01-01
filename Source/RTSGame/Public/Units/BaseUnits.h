// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Units/BaseAIControllerUnits.h"
#include "Buildings/SelectionEvent.h"
#include "Units/UnitActions.h"
#include "Units/SelectComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseUnits.generated.h"

UENUM(BlueprintType)
enum class EUnitState : uint8
{
	None UMETA(DisplayName = "None"),
	Idle UMETA(DisplayName = "Idle"),
	Movement UMETA(DisplayName = "Movement"),
	Mining UMETA(DisplayName = "Mining"),
	Attacking UMETA(DisplayName = "Attacking")
};

UCLASS()
class RTSGAME_API ABaseUnits : public ACharacter, public ISelectionEvent, public IUnitActions
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseUnits();

	UFUNCTION()
	void SetTeam_Implementation(uint8 const& id) override;
	UFUNCTION()
	FGenericTeamId GetGenericTeamId_Implementation() const override;

	UPROPERTY(EditAnywhere)
	FGenericTeamId TeamId;

	UPROPERTY(EditAnywhere)
	class UBaseHealthBarWidgetComponent* HealthBarWidgetComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	virtual void SelectThis() override;
	virtual void DeselectThis() override;

	UFUNCTION()
	void OnKillEnemy(TEnumAsByte<ETeamAttitude::Type> TeamAttitude);

	UPROPERTY(EditAnywhere)
	class USelectComponent* SelectionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBaseUnitComponent* UnitComponent;

	class ABasePlayerController* PlayerController;

	UPROPERTY()
	class ABaseAIControllerUnits* AIControllerUnits;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

};
