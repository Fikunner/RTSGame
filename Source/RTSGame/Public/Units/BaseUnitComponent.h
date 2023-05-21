// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GenericTeamAgentInterface.h"
#include "Units/BaseWorker.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseUnitComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnterNewStateDelegate, EUnitState, UnitStateNew);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKillUnitDelegate, TEnumAsByte<ETeamAttitude::Type>, Team);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTSGAME_API UBaseUnitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseUnitComponent();

	UPROPERTY(BlueprintAssignable)
	FOnEnterNewStateDelegate OnEnterNewStateDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnKillUnitDelegate OnKillUnitDelegate;

	UPROPERTY(BlueprintReadWrite)
	EUnitState StateOfUnit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	TEnumAsByte<ETeamAttitude::Type> TeamAttitude;

	UPROPERTY(EditAnywhere, Category = "Color settings")
	FLinearColor FriendlyColor;

	UPROPERTY(EditAnywhere, Category = "Color settings")
	FLinearColor NeutralColor;

	UPROPERTY(EditAnywhere, Category = "Color settings")
	FLinearColor HostileColor;

	UPROPERTY(EditAnywhere, Category = "Gamemode settings")
	float Health;
	UPROPERTY(EditAnywhere, Category = "Gamemode settings")
	float HealthMax = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamemode settings")
	float DamageToApply = 10.f;

	UFUNCTION(BlueprintCallable)
	void HandleNewUnitState(EUnitState NewUnitState);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddUnitToSelectionList();

protected:
	
	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnOwnerClicked(AActor* TouchedActor, FKey ButtonPressed);
	UFUNCTION()
	void OnOwnerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UFUNCTION()
	void UpdateHealthBar();

	UPROPERTY()
	class ABasePlayerController* PlayerController;
	UPROPERTY()
	class UBaseHealthBarWidgetComponent* HealthBarWidgetComponent;
};
