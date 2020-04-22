// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessGenerator.h"
#include "BackgroundClouds.h"
#include "Components/BoxComponent.h" 


// Sets default values for this component's properties
UEndlessGenerator::UEndlessGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
}


// Called when the game starts
void UEndlessGenerator::BeginPlay()
{
	Super::BeginPlay();

	// ...
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

		Cloud->SetActorLocation(Cloud->GetActorLocation() + Offset);

		float RandVariable = FMath::RandRange(1.0f, 3.0f);
		Cloud->SetMovingSpeed(RandVariable);
		Cloud->SetActorScale3D(FVector(RandVariable / 3.0f, RandVariable / 3.0f, RandVariable / 3.0f));
	}
}

// Called every frame
void UEndlessGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

