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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ResourceMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

UENUM()
enum class EResourceTypes : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Gold = 1 UMETA(DisplayName = "Gold"),
	Wood = 2 UMETA(DisplayName = "Wood")
};
