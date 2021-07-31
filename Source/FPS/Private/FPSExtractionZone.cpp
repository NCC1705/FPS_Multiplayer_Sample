// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPS/FPSCharacter.h"
#include "FPS/FPSGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	OverlapComp->SetHiddenInGame(false);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this,&AFPSExtractionZone::HandleOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f);//FVector(200.0f,200.0f,200.0f);
	DecalComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
//void AFPSExtractionZone::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

void AFPSExtractionZone::HandleOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);

	if (MyPawn == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone"));

	if (MyPawn && MyPawn->bIsCarryingObjective)
	{
		AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)//game mode is null on client, this fails on all clients
		{
			GM->CompleteMission(MyPawn,true);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
		//:: because functions are marked as static
		//useful for function to do stuff whilenot associated with any object instance
		//just playing a sound - passes it on to the audio engine
		//gameplay statics - play sounds, spawn emitters etc
	}
	
	
}

// Called every frame
//void AFPSExtractionZone::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

