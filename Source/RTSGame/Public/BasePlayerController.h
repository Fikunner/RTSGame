// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Buildings/BuildingComponent.h"
#include "Units/BaseUnitComponent.h"
#include "Resources/BaseResource.h"
#include "Units/BaseAIControllerUnits.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "Buildings/SelectionEvent.h"
#include "Units/UnitActions.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ABasePlayerController : public APlayerController, public ISelectionEvent, public IUnitActions
{
	GENERATED_BODY()
	
public:

	ABasePlayerController();

	UFUNCTION(BlueprintCallable)
	void ReceiveResources(EResourceTypes ResourceType, int32 Amount, int HowMuchToSubstractFromMaxValue);

	UFUNCTION()
	void AddActorSelectedToList(AActor* SelectedActor);

	UFUNCTION()
	void DeselectAllActors();

	UFUNCTION()
	virtual void SelectThisActor(AActor* SelectedActor) override;
	
	UFUNCTION()
	virtual void DeselectThisActor(AActor* DeselectedActor) override;

	UFUNCTION()
	virtual void ClickSelectThisActor(AActor* SelectedActor) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EResourceTypes, int32> StoredResource;

	UPROPERTY()
	TArray<class AActor*> OutActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AUnitSelectionMarquee* SelectionMarqueeRef;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AUnitSelectionMarquee> UnitSelectionMarqueeToSpawn;

	UFUNCTION()
	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION()
	virtual void SetupInputComponent() override;

	UFUNCTION()
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Movement")
	float ViewportEdgeTreshold = 0.02;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Movement")
	float MouseForwardScale;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Movement")
	float MouseRightScale;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* NS_ClickIndicator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SelectedActors;

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<UActorComponent> ResourceComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<UActorComponent> BuildingComp;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UBaseUnitComponent* UnitComponent;


private:

	UPROPERTY()
	bool IsClickSelected;

	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);
	UFUNCTION()
	void MouseMovement(float Value);

	UFUNCTION()
	void MouseSelection();
	UFUNCTION()
	void MouseDeselection();

	UFUNCTION()
	void MouseAction();

	UFUNCTION()
	void OpenMenu();

	bool IsOpenMenu;

	UPROPERTY()
	class ABaseBuildings* BuildingBase;
	UPROPERTY()
	class ABaseAIControllerUnits* AIControllerUnits;
	UPROPERTY()
	class ABaseHUD* HUD;

};
