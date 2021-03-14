// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlackHoleGameMode.generated.h"

UCLASS(minimalapi)
class ABlackHoleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABlackHoleGameMode();

	void CompleteMission(bool &flagComplete, APawn* InstigatorPawn);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn);
};



