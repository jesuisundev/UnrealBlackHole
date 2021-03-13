// Fill out your copyright notice in the Description page of Project Settings.


#include "RootBlackHole.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARootBlackHole::ARootBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectiveMesh"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("ObjetiveSphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);

	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("ObjetiveSphereCompTwo"));
	InnerSphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	InnerSphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	InnerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARootBlackHole::OnBlackHoleRootHit);
	InnerSphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void ARootBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARootBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OutOverlappingComponents{};
	forceOnComponent = forceOnComponent - 2000;
	SphereComp->GetOverlappingComponents(OutOverlappingComponents);

	for (UPrimitiveComponent* OutOverlappingComponent : OutOverlappingComponents)
	{
		OutOverlappingComponent->AddRadialForce(MeshComp->GetRelativeLocation(), 10000, forceOnComponent, ERadialImpulseFalloff::RIF_Linear);
	}
}

void ARootBlackHole::OnBlackHoleRootHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		OtherActor->Destroy();
	}
}