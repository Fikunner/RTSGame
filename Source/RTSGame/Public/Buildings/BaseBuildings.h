// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Buildings/SelectionEvent.h"
#include "Components/StaticMeshComponent.h"
#include "SelectionEvent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBuildings.generated.h"

UCLASS()
class RTSGAME_API ABaseBuildings : public AActor, public ISelectionEvent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBuildings();

	UFUNCTION()
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BuildingClicked();

	virtual void DeselectThis() override;
	
	UPROPERTY(EditAnywhere)
	class UBuildingComponent* BuildingComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDecalComponent* Decal;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

UENUM(BlueprintType)
enum class EBuildingTypes : uint8
{
	None UMETA(DisplayName = "None"),
	TownHall UMETA(DisplayName = "TownHall"),
	House UMETA(DisplayName = "House"),
	Barrack UMETA(DisplayName = "Barrack")
};
