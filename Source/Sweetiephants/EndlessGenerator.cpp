// Fill out your copyright notice in the Description page of Project Settings.

#include "EndlessGenerator.h"
#include "MainCamera.h"
#include "BackgroundClouds.h"
#include "BaseEnemy.h"
#include "Components/BoxComponent.h" 
#include "EatableObjects.h"


UEndlessGenerator::UEndlessGenerator()
{
	PrimaryComponentTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
}

void UEndlessGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (Trigger)
	{
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &UEndlessGenerator::OnOverlapBegin);
	}
}

void UEndlessGenerator::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
										AActor* OtherActor,
										UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex,
										bool bFromSweep, const
										FHitResult& SweepResult)
{
	if (OtherActor->IsA<ABackgroundClouds>())
	{
		Cloud = Cast<ABackgroundClouds>(OtherActor);

		FVector SpawnPosition;
		SpawnPosition = FVector(
			Cloud->GetActorLocation().X + Offset.X,
			Cloud->GetActorLocation().Y,
			GetOwner()->GetActorLocation().Z + FMath::RandRange(-300.0f, 500.0f));

		Cloud->SetActorLocation(SpawnPosition);

		float RandVariable = FMath::RandRange(1.0f, 3.0f);
		Cloud->SetMovingSpeed(RandVariable);
		Cloud->SetActorScale3D(FVector(RandVariable / 3.0f, RandVariable / 3.0f, RandVariable / 3.0f));
	}
}

