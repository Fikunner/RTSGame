// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "BasePlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Buildings/SelectionEvent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitSelectionMarquee.generated.h"

UCLASS()
class RTSGAME_API AUnitSelectionMarquee : public AActor, public ISelectionEvent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitSelectionMarquee();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldResizeMarquee;

	UFUNCTION()
	void StartResizingMarquee();

	UFUNCTION()
	void EndResizingMarquee();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* SphereOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* SphereTwo;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	class ABasePlayerController* PlayerController;

};
