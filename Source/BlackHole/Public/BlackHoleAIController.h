// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BlackHoleAIController.generated.h"

/**
 * 
 */
UCLASS()
class BLACKHOLE_API ABlackHoleAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "TargetPoint")
	TSubclassOf<AActor> FirstTargetClass;

	void StartPatrol();

	void GetFirstTargetPoint(AActor* FirstTargetPoint);
};
