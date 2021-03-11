// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlackHoleGameMode.h"
#include "BlackHoleHUD.h"
#include "BlackHoleCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlackHoleGameMode::ABlackHoleGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABlackHoleHUD::StaticClass();
}
