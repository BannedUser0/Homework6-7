// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_homework7.h"
#include "PlayerController_homework7.h"
#include "Pawn_homework7.h"

AGameMode_homework7::AGameMode_homework7()
{
	DefaultPawnClass = APawn_homework7::StaticClass();
	PlayerControllerClass = APlayerController_homework7::StaticClass();
}
