// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,

	Suspicious,

	Alerted
};

UCLASS()
class BLACKHOLE_API AAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Sensor")
	UPawnSensingComponent* PawnSensingComp;


	// we need that otherwise the code will not be able to bind this to the event via adddynamic
	UFUNCTION()
	void HandleOnSeePawn(APawn* SeenPawn);

	UFUNCTION()
	void HandleOnHearNoise(APawn* HeardPawn, const FVector& Location, float Volume);

	FRotator OriginalRotation;

	UFUNCTION()
	void resetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

	EAIState GuardState;

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChange(EAIState NewState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
