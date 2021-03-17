// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "BlackHole/BlackHoleGameMode.h"

// Sets default values
AAIGuard::AAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawefewfwmSensingComponent"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGuard::HandleOnSeePawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAIGuard::HandleOnHearNoise);

	GuardState = EAIState::Idle;
}

// Called when the game starts or when spawned
void AAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalRotation = GetActorRotation();
}

void AAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}

	GuardState = NewState;

	OnStateChange(GuardState);
}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AAIGuard::HandleOnSeePawn(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);

	ABlackHoleGameMode* GM = Cast<ABlackHoleGameMode>(GetWorld()->GetAuthGameMode());

	if (GM)
	{
		bool garbageToDel;
		GM->CompleteMission(garbageToDel, SeenPawn, false);
	}

	SetGuardState(EAIState::Alerted);
}

void AAIGuard::HandleOnHearNoise(APawn* HeardPawn, const FVector& Location, float Volume)
{
	if (HeardPawn == nullptr)
	{
		return;
	}

	if (GuardState == EAIState::Alerted)
	{
		return;
	}


	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;
	
	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AAIGuard::resetOrientation, 3.0f);

	SetGuardState(EAIState::Suspicious);
}

void AAIGuard::resetOrientation()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	SetActorRotation(OriginalRotation);

	SetGuardState(EAIState::Idle);
}
