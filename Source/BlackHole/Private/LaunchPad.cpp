// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "BlackHole/BlackHoleCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
	PrimaryActorTick.bCanEverTick = false;

	LaunchpadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchpadMesh"));
	LaunchpadMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = LaunchpadMesh;

	LaunchPad = CreateDefaultSubobject<UBoxComponent>(TEXT("Launchpad"));
	LaunchPad->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LaunchPad->SetCollisionResponseToAllChannels(ECR_Ignore);
	LaunchPad->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	LaunchPad->SetBoxExtent(FVector(100.0f, 100.0f, 50.0f));

	LaunchPad->SetHiddenInGame(false);

	LaunchPad->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::HandleOverlap);

	LaunchPad->SetupAttachment(LaunchpadMesh);
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();
}

void ALaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped with launchpad"));

	if (OtherActor == nullptr)
	{
		return;
	}

	ABlackHoleCharacter* MyPawn = Cast<ABlackHoleCharacter>(OtherActor);

	if (MyPawn)
	{
		MyPawn->LaunchCharacter(FVector(2000.0f, 0, 2000.0f), true, true);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("In first else"));
		if (OtherComp)
		{
			OtherComp->AddImpulse(FVector(2000.0f, 0, 2000.0f), NAME_None, true);
		}
	}
}

