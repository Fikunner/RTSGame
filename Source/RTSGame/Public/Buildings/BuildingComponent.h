// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Buildings/BaseBuildings.h"
#include "Components/WidgetComponent.h"
#include "GenericTeamAgentInterface.h"
#include "Buildings/GoalLocation.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingDestroyedDelegate, TEnumAsByte<ETeamAttitude::Type>, Team);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTSGAME_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingComponent();

	UPROPERTY(BlueprintAssignable)
	FOnBuildingDestroyedDelegate OnBuildingDestroyed;

	UPROPERTY(EditAnywhere)
	FVector2D HealthBarDrawSize;

	class UBaseHealthBarWidgetComponent* HealthBarWidgetComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBuildingTypes TypeOfBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETeamAttitude::Type> TeamAttitude;

	UFUNCTION()
	void UpdateHealthBar();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetSuitableLocation(UGoalLocation*& SuitableLocationRef);

	UFUNCTION()
	void OnOwnerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthMax = 400;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
