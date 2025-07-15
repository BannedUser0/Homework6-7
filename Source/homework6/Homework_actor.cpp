// Fill out your copyright notice in the Description page of Project Settings.


#include "Homework_actor.h"
#include "SpawnActor.h"
#include "EngineUtils.h"

// Sets default values
AHomework_actor::AHomework_actor()
{
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Scene);

	StaticComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticComponent->SetupAttachment(Scene);

	NormalRotateValue = FRotator(0.0f, 0.0f, 0.0f);
	NormalMoveValue = FVector(0.0f, 0.0f, 0.0f);

	StartPosition = GetActorLocation();
	PartolTarget = FVector(0.0f, 0.0f, 0.0f);
	PatrolSpeed = 1.f;
	IsArrive = false;
	ObjectModeCheck = ObjectMode::Random;
	NormalTrasformValue = FVector(0.0f, 0.0f, 0.0f);

}

void AHomework_actor::BeginPlay()
{
	Super::BeginPlay();

	if (ObjectModeCheck == ObjectMode::Random)
	{
		ActorTimer();

		GetWorldTimerManager().SetTimer(
		ActorTimerHandle,
		this,
		&AHomework_actor::ActorTimer,
		5.0f,
		true
		);
	}
}

void AHomework_actor::ActorTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("its work"));
	NormalRotateValue = FRotator(RandomNumber(), RandomNumber(), RandomNumber());
	NormalMoveValue = FVector(RandomNumber(), RandomNumber(), RandomNumber());
	StaticComponent->AddWorldOffset(40*FVector(RandomNumber(), RandomNumber(), RandomNumber()));
}

float AHomework_actor::RandomNumber()
{
	float num = FMath::RandRange(-10.f, 10.f);
	return num;
}


void AHomework_actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ObjectModeCheck == ObjectMode::Normal || ObjectModeCheck == ObjectMode::Random)
	{
		StaticComponent->AddLocalRotation(NormalRotateValue * DeltaTime);
		StaticComponent->AddWorldOffset(NormalMoveValue * DeltaTime);
		
		

	}
	else if (ObjectModeCheck == ObjectMode::Patrol)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, PartolTarget, DeltaTime, PatrolSpeed);

		SetActorLocation(NewLocation);

		if (FVector::Dist(NewLocation, PartolTarget) <= 10.0f)
		{
			SetActorLocation(PartolTarget);
			ObjectModeCheck = ObjectMode::Return;
			UE_LOG(LogTemp, Warning, TEXT("Change mode: Return"));
		}
	}
	else if (ObjectModeCheck == ObjectMode::Return)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, StartPosition, DeltaTime, PatrolSpeed);

		SetActorLocation(NewLocation);

		if (FVector::Dist(NewLocation, StartPosition) <= 10.0f)
		{
			SetActorLocation(StartPosition);
			ObjectModeCheck = ObjectMode::Patrol;
			UE_LOG(LogTemp, Warning, TEXT("Change mode: Patrol"));
		}
	}

}


