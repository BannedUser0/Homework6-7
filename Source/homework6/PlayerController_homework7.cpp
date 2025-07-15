// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_homework7.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"


APlayerController_homework7::APlayerController_homework7() :
	InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr)
{
}

void APlayerController_homework7::BeginPlay()
{
	Super::BeginPlay();
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem
			= LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0); // 우선순위 0으로 설정  
			}
		}
	}
}
