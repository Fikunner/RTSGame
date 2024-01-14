// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySpawner.h"
#include "NavigationSystem.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereCollision->SetSphereRadius(1500.f);

	TimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemySpawner::SpawnWave);
	CurrentWaveOrder = -1;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, TimerDelegate, WavesStruct[0].SpawnDelay, false);

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy(TSubclassOf<AActor> ActorToSpawn, int EnemiesToSpawn)
{
	const FVector Location = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), WavesStruct[CurrentWaveOrder].SpawnRadius);
	const FRotator Rotation = GetActorRotation();
	FActorSpawnParameters SpawnInfo;

	GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location + FVector(0.f, 0.f, 100.f), Rotation, SpawnInfo);
}

void AEnemySpawner::SpawnWave()
{
	CurrentWaveOrder++;

	if (CurrentWaveOrder < WavesStruct.Num())
	{
		FWaveStruct& CurrentWave = WavesStruct[CurrentWaveOrder];
		for (TSubclassOf<AActor> ArrayElements : CurrentWave.EnemiesToSpawn)
		{
			SpawnEnemy(ArrayElements, CurrentWave.EnemiesToSpawn.Num());
			GEngine->AddOnScreenDebugMessage(-1, 2.f,FColor::White, "Spawn");
		}

		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, TimerDelegate, WavesStruct[CurrentWaveOrder].SpawnDelay, false);
	}
}
