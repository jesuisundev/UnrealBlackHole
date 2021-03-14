// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "BlackHole/BlackHoleCharacter.h"
#include "BlackHole/BlackHoleGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AExtractionZone::AExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	OverlapComp->SetHiddenInGame(false);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::HandleOverlap);

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	DecalComponent->DecalSize = FVector(200.0f);
	DecalComponent->SetupAttachment(OverlapComp);
}

// Called when the game starts or when spawned
void AExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExtractionZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction"));

	if (isExtractionDone)
	{
		UE_LOG(LogTemp, Log, TEXT("Extraction already done"));

		return;
	}

	ABlackHoleCharacter* MyPawn = Cast<ABlackHoleCharacter>(OtherActor);

	if (MyPawn == nullptr)
	{
		return;
	}

	if (MyPawn->isCarryingObjective) {
		ABlackHoleGameMode* GM = Cast<ABlackHoleGameMode>(GetWorld()->GetAuthGameMode());

		if (GM) {
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ObjectiveSuccedSound, GetActorLocation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireworkParticle, GetActorLocation());
			GM->CompleteMission(isExtractionDone, MyPawn);
		}
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ObjectiveMissingSound, GetActorLocation());
		UE_LOG(LogTemp, Log, TEXT("Objective missing"));
	}
}