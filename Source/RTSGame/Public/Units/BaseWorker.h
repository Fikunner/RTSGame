// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HUD/BaseHUD.h"
#include "Resources/BaseResource.h"
#include "Navigation/PathFollowingComponent.h"
#include "UnitActions.h"
#include "Buildings/SelectionEvent.h"
#include "HUD/BaseHealthBarWidgetComponent.h"
#include "Units/SelectionComponent.h"
#include "Components/BoxComponent.h"
#include "GenericTeamAgentInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseWorker.generated.h"

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
class RTSGAME_API ABaseWorker : public ACharacter, public IUnitActions, public ISelectionEvent
{
	GENERATED_BODY()
	
public:
	
	ABaseWorker();

	UFUNCTION()
	void MoveUnitToThisLocation_Implementation(FVector Location) override;
	UFUNCTION()
	void GatherThisResource_Implementation(AActor* ResourceRef) override;
	UFUNCTION()
	void InteractWithBuilding_Implementation(AActor* BuildingRef) override;

	UFUNCTION()
	void SetTeam_Implementation(uint8 const& id) override;
	UFUNCTION()
	FGenericTeamId GetGenericTeamId_Implementation() const override;

	UFUNCTION()
	virtual void SelectThis() override;
	UFUNCTION()
	virtual void DeselectThis() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GoToTownHallAndDepositResources(AActor* ResourceRef);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RepeatTheMiningAction(AActor* ResourceRef);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	FGenericTeamId TeamId;

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBaseUnitComponent* BaseUnitComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USelectionComponent* SelectionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* DetectEnemiesCollisions;

	UFUNCTION()
	void OnKillEnemy(TEnumAsByte<ETeamAttitude::Type> TeamAttitude);

public:	
	
	UFUNCTION()
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	void OnMoveCompletedMoveUnitToThisLocation(FAIRequestID RequestID, const FPathFollowingResult& Result);
	void OnMoveCompletedGatherThisResource(FAIRequestID RequestID, const FPathFollowingResult& Result);
	void OnMoveCompletedGoToTownHallAndDepositResources(FAIRequestID RequestID, const FPathFollowingResult& Result);

	void SetTimerWithDelegate(FTimerHandle& TimerHandle, TDelegate<void()> ObjectDelegate, float Time, bool bLoop);

	TArray<AActor*> DetectedActors;

	FTimerHandle HandleGatherThisResource;
	
	FTimerDelegate DelegateGatherThisResource;
	FTimerDelegate DelegateOnMoveCompletedGatherThisResource;
	
	UPathFollowingComponent* PathFollowingComponent;

	FRotator ResourcePosition;

	FAIRequestID Results; 
	
	class ABaseAIControllerUnits* AIControllerUnits;
	class ABaseRTSGameMode* RTSGameMode;
	class ABasePlayerController* PlayerController;
	class ABaseResource* BaseResource;
	class AGoldResource* GoldResource;
	class UResourceComponent* ResourceComponent;
	class ABaseHUD* HUD;
	UPROPERTY(EditAnywhere)
	class UBaseHealthBarWidgetComponent* HealthBarWidgetComponent;
};