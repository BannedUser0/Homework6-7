// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnActor.h"
#include "GameFramework/Actor.h"

ASpawnActor::ASpawnActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);
    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    SpawningBox->SetupAttachment(Scene);
    SpawnCount = 5;
}

void ASpawnActor::BeginPlay()
{
    Super::BeginPlay();

    for(int i = 0; i < SpawnCount; i++)
    {
        OrderSpawn();
	}
}

FVector ASpawnActor::GetRandomPositionVolume() const
{
    FVector BoxExtent = SpawningBox->GetScaledBoxExtent(); // length(200, 100, 50) scale(2, 1, 1)로 가정하면 (400, 100, 50) 이것이 적용된 값의 절반을 반환. 중심-> 끝
    FVector BoxOrigin = SpawningBox->GetComponentLocation();

    return BoxOrigin + FVector(
        FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
        FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
        FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
    );
} 

void ASpawnActor::OrderSpawn()
{
        FVector SpawnLocation = GetRandomPositionVolume();
        FRotator SpawnRotation = FRotator::ZeroRotator;

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
}

