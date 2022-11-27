// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resources/ResourceComponent.h"
#include "Resources/BaseResource.h"
#include "Navigation/PathFollowingComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseWorker.generated.h"

UCLASS()
class RTSGAME_API ABaseWorker : public ACharacter
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

	/*UFUNCTION()
	void MoveUnitToThisLocation(FVector Location);

	UFUNCTION()
	void GatherThisResource(AActor* ResourceRef);*/

	class UResourceComponent* ResourceComponent;

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

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EResourceTypes> ResourceBeingCarried;

	UPROPERTY(EditAnywhere)
	int AmountOfResources;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
	void NotifyActorOnClicked(FKey ButtonPressed);

	/*void OnMoveCompletedMoveUnitToThisLocation(FAIRequestID RequestID, const FPathFollowingResult& Result);
	void OnMoveCompletedGatherThisResource(FAIRequestID RequestID, const FPathFollowingResult& Result);*/
	
	//void SetTimerWithDelegate(FTimerHandle& TimerHandle, TBaseDelegate<void> ObjectDelegate, float Time, bool bLoop);

	//FTimerHandle HandleGatherThisResource;
	//FTimerDelegate DelegateGatherThisResource;

	//UPathFollowingComponent* PathFollowingComponent;

	FRotator ResourcePosition;

	//FAIRequestID Results;

	//class ABaseAIControllerUnits* AIControllerUnits;
	class UBaseUnitComponent* BaseUnitComponent;
	class ABaseRTSGameMode* RTSGameMode;
	class ABasePlayerController* PlayerController;
	class ABaseResource* BaseResource;

};

UENUM(BlueprintType)
enum class EUnitState : uint8
{
	None UMETA(DisplayName = "None"),
	Idle UMETA(DisplayName = "Idle"),
	Movement UMETA(DisplayName = "Movement"),
	Mining UMETA(DisplayName = "Mining"),
};