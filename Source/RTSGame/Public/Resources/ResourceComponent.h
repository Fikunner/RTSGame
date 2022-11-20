// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseResource.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTSGAME_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceComponent();

	UPROPERTY()
	TEnumAsByte<EResourceTypes> TypeOfResource;

	UPROPERTY()
	int TimeIsCanBeMined;

	UPROPERTY()
	int NumberOfResourcesToGive;

	UPROPERTY(EditAnywhere)
	float TimeItTakesToBeGatheredInSeconds = 2.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
