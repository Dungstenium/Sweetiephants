// Fill out your copyright notice in the Description page of Project Settings.


#include "EatableObjects.h"
#include "SweetiephantsCharacter.h"
#include "Components/BoxComponent.h" 
// Sets default values
AEatableObjects::AEatableObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;
}

// Called when the game starts or when spawned
void AEatableObjects::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AEatableObjects::OnOverlapBegin);
}

// Called every frame
void AEatableObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	NewLocation = this->GetActorLocation();
	DeltaHight = (FMath::Sin((ExecutionTime + DeltaTime) * FloatingSpeed) - FMath::Sin(ExecutionTime * FloatingSpeed));
	NewLocation.Z += DeltaHight * FloatingGap;
	ExecutionTime += DeltaTime;

	//Trigger->SetRelativeLocation(NewLocation);
	this->SetActorLocation(NewLocation);
}

void AEatableObjects::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor->IsA<ASweetiephantsCharacter>())
	{
		Destroy();
	}
}


