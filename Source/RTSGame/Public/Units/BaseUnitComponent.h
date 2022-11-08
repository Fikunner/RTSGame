// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseWorker.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseUnitComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterIdleDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterMovementDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterMiningDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTSGAME_API UBaseUnitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseUnitComponent();

	UPROPERTY(BlueprintAssignable)
	FOnEnterIdleDelegate OnEnterIdleDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEnterMovementDelegate OnEnterMovementDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEnterMiningDelegate OnEnterMiningDelegate;

	UPROPERTY()
	EUnitState UnitState;

	UFUNCTION()
	void HandleNewUnitState(EUnitState NewUnitState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddUnitToSelectionList();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowSelectionDecal();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnOwnerClicked(AActor* TouchedActor, FKey ButtonPressed);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	class ABasePlayerController* BasePlayerController;

};
