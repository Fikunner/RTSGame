// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resources/BaseResource.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTSGAME_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UResourceComponent(); 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EResourceTypes TypeOfResource;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TimeIsCanBeMined;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfResourcesToGive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeItTakesToBeGatheredInSeconds = 2.f;

	bool CanMineThisResource;
	
	UFUNCTION(BlueprintCallable)
	void GiveResource(EResourceTypes& TypeResource, int& NumberResourcesToGive);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanThisResourceBeMined();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
