// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class FPS_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackHole();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components");
	UStaticMeshComponent* MeshComp;

	//Inner shpere destroys the overlapping components
	UPROPERTY(VisibleAnywhere, Category = "Components");
	USphereComponent* InnerSphereComponent;

	//Outer sphere pulls components that are physically simulating towards the center of the actor
	UPROPERTY(VisibleAnywhere, Category = "Components");
	USphereComponent* OuterSphereComponent;

	//marked with ufunction to bind the overlap event
	UFUNCTION()
		void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
