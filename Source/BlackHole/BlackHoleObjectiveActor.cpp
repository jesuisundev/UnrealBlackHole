// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHoleObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABlackHoleObjectiveActor::ABlackHoleObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectiveMesh"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("ObjetiveSphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void ABlackHoleObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackHoleObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionParticle, GetActorLocation());
}

// Called every frame
void ABlackHoleObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlackHoleObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();
}

