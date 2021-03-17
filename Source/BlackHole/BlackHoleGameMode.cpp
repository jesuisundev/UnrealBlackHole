// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlackHoleGameMode.h"
#include "BlackHoleHUD.h"
#include "BlackHoleCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ABlackHoleGameMode::ABlackHoleGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABlackHoleHUD::StaticClass();
}

void ABlackHoleGameMode::CompleteMission(bool &flagComplete, APawn* InstigatorPawn, bool isSuccess)
{
	flagComplete = true;
	UE_LOG(LogTemp, Log, TEXT("EXTRACTION DONE"));

	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		TArray<AActor*> ReturnedActors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

		AActor* NewViewTarget = nullptr;
		if (ReturnedActors.Num() > 0)
		{
			NewViewTarget = ReturnedActors[0];
		}

		APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());

		if (PC)
		{
			PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}

	// Blueprint Logic Function
	OnMissionCompleted(InstigatorPawn, isSuccess);
}