// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Buildings/BaseBuildings.h"
#include "Components/WidgetComponent.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTSGAME_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingComponent();

	UPROPERTY(EditAnywhere)
	FVector2D HealthBarDrawSize = FVector2D(75, 12);

	class UBaseHealthBarWidgetComponent* HealthBarWidgetComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBuildingTypes TypeOfBuilding = EBuildingTypes::TownHall;

	void UpdateHealthBar();

	UPROPERTY(EditAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float HealthMax = 400;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
