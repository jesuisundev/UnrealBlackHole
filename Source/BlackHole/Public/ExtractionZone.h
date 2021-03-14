// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtractionZone.generated.h"

class UBoxComponent;
class UParticleSystem;

UCLASS()
class BLACKHOLE_API AExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtractionZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Component");
	UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Decal");
	UDecalComponent* DecalComponent;

	UPROPERTY(EditAnywhere, Category = "FX");
	UParticleSystem* FireworkParticle;

	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
	bool isExtractionDone{ false };

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
