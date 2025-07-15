#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Homework_actor.h"
#include "SpawnActor.generated.h"


UCLASS()
class HOMEWORK6_API ASpawnActor : public AActor
{
	GENERATED_BODY()

public:
	ASpawnActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning")
	int SpawnCount;
	// ��ġ ��� �� ���� �Լ�
	FVector GetRandomPositionVolume() const;
	

	void BeginPlay();
	void OrderSpawn();
};
