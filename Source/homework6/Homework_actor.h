#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Homework_actor.generated.h"


UENUM(BlueprintType)
enum class ObjectMode : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Random UMETA(DisplayName = "Random"),
	Patrol UMETA(DisplayName = "Patrol"),
	Return UMETA(DisplayName = "Return")
};

UCLASS()
class HOMEWORK6_API AHomework_actor : public AActor
{
	GENERATED_BODY()
	
public:	
	AHomework_actor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FRotator NormalRotateValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FVector NormalMoveValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	ObjectMode ObjectModeCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FVector	StartPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FVector PartolTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float PatrolSpeed;
	
	FTimerHandle ActorTimerHandle;
	FVector NormalTrasformValue;



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	UStaticMeshComponent* StaticComponent;
	bool IsArrive;


public:	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
	void ActorTimer();
	float RandomNumber();
};
