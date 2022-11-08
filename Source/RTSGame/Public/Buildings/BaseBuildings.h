// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePlayerController.h"
#include "Buildings/SelectionEvent.h"
#include "Components/StaticMeshComponent.h"

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
	void NotifyActorOnClicked(FKey ButtonPressed);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BuildingClicked();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DeselectThisActor();

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

	class ABasePlayerController* BasePlayerController;

};
