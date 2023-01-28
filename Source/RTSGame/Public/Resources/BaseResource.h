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
	// Sets default values for this actor's properties
	ABaseResource();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UResourceComponent* ResourceComponent;

	class ABaseWorker* Worker;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ResourceMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

UENUM(BlueprintType)
enum class EResourceTypes : uint8
{
	None UMETA(DisplayName = "None"),
	Gold UMETA(DisplayName = "Gold"),
	Wood UMETA(DisplayName = "Wood")
};
