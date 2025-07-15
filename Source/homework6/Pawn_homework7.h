// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Pawn_homework7.generated.h"

UCLASS()
class HOMEWORK6_API APawn_homework7 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawn_homework7();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera|Component")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera|Component")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character|Component")
	USkeletalMeshComponent* SkeletalComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	int MoveValue;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);

	UFUNCTION()
	void Look(const FInputActionValue& value);

	UFUNCTION()
	void FlyHigh(const FInputActionValue& value);

	UFUNCTION()
	void FlyDown(const FInputActionValue& value);

	UFUNCTION()
	void Roll(const FInputActionValue& value);

private:

	float GravityAcceleration;
	float FallVelocity;
	bool bIsMoving;
	bool bIsOnGround;


public:	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
