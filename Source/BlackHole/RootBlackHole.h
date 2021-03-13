// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RootBlackHole.generated.h"

class USphereComponent;

UCLASS()
class BLACKHOLE_API ARootBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARootBlackHole();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components");
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components");
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components");
	USphereComponent* InnerSphereComp;

	float forceOnComponent = 10000.0;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** called when projectile hits something */
	UFUNCTION()
	void OnBlackHoleRootHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
