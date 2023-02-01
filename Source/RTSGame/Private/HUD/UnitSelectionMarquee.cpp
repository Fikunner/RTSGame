// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/UnitSelectionMarquee.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AUnitSelectionMarquee::AUnitSelectionMarquee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AUnitSelectionMarquee::OnOverlapBegin);

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(DefaultSceneRoot);
	
	SphereOne = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereOne"));
	SphereOne->SetupAttachment(DefaultSceneRoot);

	SphereTwo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereTwo"));
	SphereTwo->SetupAttachment(DefaultSceneRoot);
	
}

// Called when the game starts or when spawned
void AUnitSelectionMarquee::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitSelectionMarquee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShouldResizeMarquee)
	{
		FHitResult Hit;

		PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		PlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, Hit);

		Sphere->SetWorldLocation(Hit.Location);

		FVector EndMouseLocation = Hit.Location;
		FVector StartMouseLocation = GetActorLocation();
		float Alpha = 0.5f;

		FVector SizeOfBoxCollision = (StartMouseLocation - EndMouseLocation) / 2.f;
		float HeightOfBoxCollision = 200.f;

		BoxCollision->SetWorldLocation(StartMouseLocation + (EndMouseLocation - StartMouseLocation) * Alpha);
		BoxCollision->SetBoxExtent(SizeOfBoxCollision = UKismetMathLibrary::MakeVector(SizeOfBoxCollision.X, SizeOfBoxCollision.Y, HeightOfBoxCollision));
	}

}

void AUnitSelectionMarquee::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		
}

