// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySpawner.h"
#include "NavigationSystem.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 1000.f;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereCollision->SetSphereRadius(SphereRadius);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	Time = 10.f;

	TimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemySpawner::SpawnWave);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, TimerDelegate, Time, true);

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy(int EnemiesToSpawn)
{
	for (int i = 1; i <= EnemiesToSpawn; i++)
	{
		const FVector Location = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), SphereRadius);
		const FRotator Rotation = GetActorRotation();
		FActorSpawnParameters SpawnInfo;

		GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location + FVector(0.f, 0.f, 100.f), Rotation, SpawnInfo);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::SanitizeFloat(Time));
	}
}

void AEnemySpawner::SpawnWave()
{
	SpawnEnemy(FMath::RandRange(1, 2));
}
