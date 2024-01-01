// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimMontage.h"
#include "HUD/BaseHUD.h"
#include "Resources/BaseResource.h"
#include "Navigation/PathFollowingComponent.h"
#include "UnitActions.h"
#include "Buildings/SelectionEvent.h"
#include "HUD/BaseHealthBarWidgetComponent.h"
#include "Components/BoxComponent.h"
#include "GenericTeamAgentInterface.h"
#include "CoreMinimal.h"
#include "Units/BaseUnit.h"
#include "BaseWorker.generated.h"

UCLASS()
class RTSGAME_API ABaseWorker : public ABaseUnit
{
	GENERATED_BODY()

public:

	ABaseWorker();

	UFUNCTION()
	void GatherThisResource_Implementation(AActor* ResourceRef) override;
	UFUNCTION()
	void InteractWithBuilding_Implementation(AActor* BuildingRef) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GoToTownHallAndDepositResources(AActor* ResourceRef);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RepeatTheMiningAction(AActor* ResourceRef);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* DetectEnemiesCollisions;

	UFUNCTION()
	void OnKillEnemy(TEnumAsByte<ETeamAttitude::Type> TeamAttitude);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationMontage");
	UAnimMontage* FirstAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationMontage");
	UAnimMontage* SecondAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationMontage");
	UAnimMontage* ThirdAttack;
public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void OnMoveCompletedGatherThisResource(FAIRequestID RequestID, const FPathFollowingResult& Result);
	void OnMoveCompletedGoToTownHallAndDepositResources(FAIRequestID RequestID, const FPathFollowingResult& Result);

	void SetTimerWithDelegate(FTimerHandle& TimerHandle, TDelegate<void()> ObjectDelegate, float Time, bool bLoop);

	TArray<AActor*> DetectedActors;

	FTimerHandle HandleGatherThisResource;

	FTimerDelegate DelegateGatherThisResource;
	FTimerDelegate DelegateOnMoveCompletedGatherThisResource;

	FRotator ResourcePosition;

	class ABaseAIControllerUnits* AIControllerUnits;
	class ABaseRTSGameMode* RTSGameMode;
	class ABaseResource* BaseResource;
	class AGoldResource* GoldResource;
	class UResourceComponent* ResourceComponent;
	class ABaseHUD* HUD;
};