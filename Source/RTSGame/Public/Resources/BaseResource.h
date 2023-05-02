// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseResource.generated.h"

UCLASS()
class RTSGAME_API ABaseResource : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABaseResource();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UResourceComponent* ResourceComponent;

	UPROPERTY()
	class ABaseWorker* Worker;
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ResourceMesh;

public:	
	
	virtual void Tick(float DeltaTime) override;

};

UENUM(BlueprintType)
enum class EResourceTypes : uint8
{
	None UMETA(DisplayName = "None"),
	Gold UMETA(DisplayName = "Gold"),
	Wood UMETA(DisplayName = "Wood")
};
