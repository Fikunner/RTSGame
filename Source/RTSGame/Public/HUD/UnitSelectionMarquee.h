// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "BasePlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Buildings/SelectionEvent.h"
#include "BaseHUD.h"
#include "BaseUserWidgetHUD.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitSelectionMarquee.generated.h"

UCLASS()
class RTSGAME_API AUnitSelectionMarquee : public AActor, public ISelectionEvent
{
	GENERATED_BODY()
	
public:	
	
	AUnitSelectionMarquee();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldResizeMarquee;

	UFUNCTION()
	void StartResizingMarquee();

	UFUNCTION()
	void EndResizingMarquee();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY()
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollision;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	

	virtual void Tick(float DeltaTime) override;

private:

	class ABasePlayerController* PlayerController;
	class ABaseHUD* HUD;

};
