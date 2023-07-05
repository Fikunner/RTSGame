// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class RTSGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEnemySpawner();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnEnemy(int EnemiesToSpawn);

	UPROPERTY(EditAnywhere)
	int HowMuchEnemiesToSpawn;

	UPROPERTY(EditAnywhere)
	float Time;

	UPROPERTY(EditAnywhere)
	float SphereRadius;

	UPROPERTY(EditAnywhere, Category = "Actor")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereCollision;

public:	
	
	virtual void Tick(float DeltaTime) override;

private:

	void SpawnWave();
	
	float RandomDelay;

	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemySpawner::SpawnWave);
	FTimerHandle SpawnTimer;

};
