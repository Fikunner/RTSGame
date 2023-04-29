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
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, Category = "Actor")
	TSubclassOf<AActor> ActorToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnEnemy(int EnemiesToSpawn);

	UPROPERTY(EditAnywhere)
	int HowMuchEnemiesToSpawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void SpawnWave();
	
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemySpawner::SpawnWave);
	FTimerHandle SpawnTimer;

	float Time;
	float RandomDelay;
	float SphereRadius;

};
