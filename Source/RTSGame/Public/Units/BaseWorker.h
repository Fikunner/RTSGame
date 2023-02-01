// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resources/BaseResource.h"
#include "Navigation/PathFollowingComponent.h"
#include "UnitActions.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseWorker.generated.h"

UCLASS()
class RTSGAME_API ABaseWorker : public ACharacter, public IUnitActions
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ABaseWorker();

	UFUNCTION()
	void OnEnterIdle();
	UFUNCTION()
	void OnEnterMovement();
	UFUNCTION()
	void OnEnterMining();

	void MoveUnitToThisLocation_Implementation(FVector Location) override;

	void GatherThisResource_Implementation(AActor* ResourceRef) override;

	void InteractWithBuilding_Implementation(AActor* BuildingRef) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GoToTownHallAndDepositResources(AActor* ResourceRef);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RepeatTheMiningAction(AActor* ResourceRef);

//	UResourceComponent* ResourceComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UDecalComponent* Decal;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimMontage* AnimMontageMining;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimationAsset* AnimationOfWalkFWD;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimationAsset* AnimationIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBaseUnitComponent* BaseUnitComponent;

	//UPROPERTY(EditAnywhere)
	//EResourceTypes ResourceBeingCarried;

	//UPROPERTY(EditAnywhere)
	//int AmountOfResources;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	void OnMoveCompletedMoveUnitToThisLocation(FAIRequestID RequestID, const FPathFollowingResult& Result);
	void OnMoveCompletedGatherThisResource(FAIRequestID RequestID, const FPathFollowingResult& Result);
	void OnMoveCompletedGoToTownHallAndDepositResources(FAIRequestID RequestID, const FPathFollowingResult& Result);

	void SetTimerWithDelegate(FTimerHandle& TimerHandle, TBaseDelegate<void>(ObjectDelegate), float Time, bool bLoop);

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
	
};

UENUM(BlueprintType)
enum class EUnitState : uint8
{
	None UMETA(DisplayName = "None"),
	Idle UMETA(DisplayName = "Idle"),
	Movement UMETA(DisplayName = "Movement"),
	Mining UMETA(DisplayName = "Mining"),
};