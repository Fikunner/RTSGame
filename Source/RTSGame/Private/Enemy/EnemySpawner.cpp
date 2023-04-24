// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySpawner.h"
#include "NavigationSystem.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComponent->SetSphereRadius(70.f);
}

void AEnemySpawner::SpawnEnemy()
{
	UNavigationSystemV1::GetRandomPointInNavigableRadius(GetWorld(), GetActorLocation(), SphereComponent->GetScaledSphereRadius());
	//AActor* SpawnedActor = GetWorld()->SpawnActor<>()
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnEnemy();

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

