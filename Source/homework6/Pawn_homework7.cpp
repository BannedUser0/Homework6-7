// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn_homework7.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "PlayerController_homework7.h"


// Sets default values
APawn_homework7::APawn_homework7()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	// root
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	CapsuleComponent->SetSimulatePhysics(false);
	RootComponent = CapsuleComponent;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	// skeletal
	SkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalComp->SetSimulatePhysics(false);
	SkeletalComp->SetRelativeLocation(FVector(0.0f, 0.0f, -44.0f));
	SkeletalComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SkeletalComp->SetRelativeScale3D(FVector(0.45f, 0.45f, 0.45f));
	SkeletalComp->SetupAttachment(RootComponent);

	// springArm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	SpringArmComp->SetupAttachment(SkeletalComp, USpringArmComponent::SocketName);
	SpringArmComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	SpringArmComp->bUsePawnControlRotation = true;

	// camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	CameraComp->bUsePawnControlRotation = false;

	MoveValue = 3;

	GravityAcceleration = -980.0f;
	FallVelocity = 0.0f;
	bIsOnGround = false;
}

// Called when the game starts or when spawned
void APawn_homework7::BeginPlay()
{
	Super::BeginPlay();
	
}

void APawn_homework7::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FallVelocity += GravityAcceleration * DeltaTime;

	// �ٴ� ������ ���� ���� Ʈ���̽�
	FHitResult HitResult;
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + FVector(0, 0, -50.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// UWorld �����͸� ���� ���
	UWorld* World = GetWorld();
	if (World)
	{
		bool bHit = World->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECC_Visibility,
			QueryParams
		);

		// ����� ���� �׸���
		DrawDebugLine(
			World,
			StartLocation,
			EndLocation,
			FColor::Red,
			false,
			-1.f,
			0,
			1.f
		);

		if (bHit||bIsMoving==true)
		{
			FallVelocity = 0.0f;
			bIsOnGround = true;
			MoveValue = 3.0f;	
		}

		else if(!bHit)
		{
			FVector FallMovement(0, 0, FallVelocity * DeltaTime);
			AddActorWorldOffset(FallMovement);
		}

	}
	bIsMoving = false;
}

void APawn_homework7::Move(const FInputActionValue& value)
{
	if (!Controller) return; // ��Ʈ�ѷ��� ������ ����, �����ڵ�

	const FVector2D MoveInput = value.Get<FVector2D>(); // FInputActionValue���� FVector2D�� ��ȯ

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		//AddMovementInput(GetActorForwardVector(), MoveInput.X);
		AddActorLocalOffset(FVector(MoveInput.X*MoveValue,0,0));
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		//AddMovementInput(GetActorRightVector(), MoveInput.Y);
		AddActorLocalOffset(FVector(0, MoveInput.Y*MoveValue, 0));
	}
}

void APawn_homework7::Look(const FInputActionValue& value)
{
	//AddControllerYawInput(LookInput.X); // �¿� ȸ��
	//AddControllerPitchInput(LookInput.Y); // ���� ȸ��

	const FVector2D LookInput = value.Get<FVector2D>();
	
	float YRotate = FMath::Clamp(LookInput.Y, 0, 20.f);
	float XRotate = FMath::Clamp(LookInput.X, 0, 20.f);
	AddActorLocalRotation(FRotator(YRotate, XRotate, 0));

	FRotator ControlRotation = Controller->GetControlRotation();
	float NewPitch = FMath::Clamp(ControlRotation.Pitch + LookInput.Y, -80.0f, 80.0f);
	Controller->SetControlRotation(FRotator(NewPitch, ControlRotation.Yaw + LookInput.X, 0.0f));
}

void APawn_homework7::FlyHigh(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		bIsMoving = true;
		bIsOnGround= false;
		MoveValue = 10.0f;
		AddActorLocalOffset(FVector(0, 0, 10));
	}
}

void APawn_homework7::FlyDown(const FInputActionValue& value)
{
	if (value.Get<bool>()&& !bIsOnGround)
	{
		AddActorLocalOffset(FVector(0, 0, -10));
	}
}

void APawn_homework7::Roll(const FInputActionValue& value)
{
	float roll = value.Get<float>();
	AddActorLocalRotation(FRotator(0, 0, roll*20));
}

void APawn_homework7::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APlayerController_homework7* PlayerController = Cast<APlayerController_homework7>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction, // �츮�� ���� IA �ҷ���
					ETriggerEvent::Triggered, // ������ ���� �ߵ�
					this, // ���� Ŭ���� : ĳ����
					&APawn_homework7::Move  // MoveAction�� �ߵ��Ǿ����� Move�� ����
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered, // LookAction�� �ߵ��Ǿ�����
					this,
					&APawn_homework7::Look
				);
			}

			if (PlayerController->FlyHighAction)
			{
				EnhancedInput->BindAction(
					PlayerController->FlyHighAction,
					ETriggerEvent::Triggered, // LookAction�� �ߵ��Ǿ�����
					this,
					&APawn_homework7::FlyHigh
				);
			}

			if (PlayerController->FlyDownAction)
			{
				EnhancedInput->BindAction(
					PlayerController->FlyDownAction,
					ETriggerEvent::Triggered, // LookAction�� �ߵ��Ǿ�����
					this,
					&APawn_homework7::FlyDown
				);
			}

			if (PlayerController->RollAction)
			{
				EnhancedInput->BindAction(
					PlayerController->RollAction,
					ETriggerEvent::Triggered, // LookAction�� �ߵ��Ǿ�����
					this,
					&APawn_homework7::Roll
				);
			}
		}
	}
}