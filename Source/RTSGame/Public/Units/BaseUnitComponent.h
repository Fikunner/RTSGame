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

	UPROPERTY(BlueprintReadWrite)
	EUnitState StateOfUnit;

	float Health; 
	float HealthMax = 100.f;

	UFUNCTION(BlueprintCallable)
	void HandleNewUnitState(EUnitState NewUnitState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddUnitToSelectionList();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowSelectionDecal();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideSelectionDecal();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnOwnerClicked(AActor* TouchedActor, FKey ButtonPressed);

	UFUNCTION()
	void OnOwnerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	void UpdateHealthBar();

	class ABasePlayerController* PlayerController;
	class UBaseHealthBarWidgetComponent* HealthBarWidgetComponent;
};
