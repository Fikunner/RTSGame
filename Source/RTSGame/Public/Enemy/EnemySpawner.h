// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

USTRUCT(BlueprintType)
struct FWaveStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> EnemiesToSpawn;

	UPROPERTY(EditAnywhere)
	float SpawnDelay;

	UPROPERTY(EditAnywhere)
	float SpawnRadius;

	FWaveStruct()
	{
		SpawnDelay = 10.f;
		SpawnRadius = 1500.f;
	}
};

UCLASS()
class RTSGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEnemySpawner();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnEnemy(TSubclassOf<AActor> ActorToSpawn, int EnemiesToSpawn);

	UPROPERTY(EditAnywhere)
	TArray<FWaveStruct> WavesStruct;

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereCollision;

public:	
	
	virtual void Tick(float DeltaTime) override;

private:

	void SpawnWave();
	
	int CurrentWaveOrder;

	float RandomDelay;

	FTimerDelegate TimerDelegate;
	FTimerHandle SpawnTimer;

};
