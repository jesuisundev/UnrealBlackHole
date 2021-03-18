// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHoleAIController.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void ABlackHoleAIController::BeginPlay()
{
	Super::BeginPlay();

	StartPatrol();
}

void ABlackHoleAIController::StartPatrol()
{
	UE_LOG(LogTemp, Log, TEXT("StartPatrol"));

	UE_LOG(LogTemp, Log, TEXT("AIController : %s"), *(this->GetName()));
	UE_LOG(LogTemp, Log, TEXT("AIController : %s"), *(this->GetFullName()));

	AActor* FirstTargetPoint = nullptr;
	GetFirstTargetPoint(FirstTargetPoint);

	if (&FirstTargetPoint == nullptr) {
		UE_LOG(LogTemp, Log, TEXT("FirstTargetPoint NULL"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Move to FirstTargetPoint"));

	MoveToActor(FirstTargetPoint);
}

void ABlackHoleAIController::GetFirstTargetPoint(AActor* FirstTargetPoint)
{
	UE_LOG(LogTemp, Log, TEXT("GetFirstTargetPoint"));

	TArray<AActor*> ReturnedActors;
	UGameplayStatics::GetAllActorsOfClass(this, FirstTargetClass, ReturnedActors);

	if (ReturnedActors.Num() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("ReturnedActors.Num(): %d"), ReturnedActors.Num());
		UE_LOG(LogTemp, Log, TEXT("SET FirstTargetPoint"));
		UE_LOG(LogTemp, Log, TEXT("SET FirstTargetPoint : %s"), *(ReturnedActors[0]->GetName()));
		UE_LOG(LogTemp, Log, TEXT("SET FirstTargetPoint : %s"), *(ReturnedActors[0]->GetFullName()));

		FirstTargetPoint = ReturnedActors[0];
	}
}