// Fill out your copyright notice in the Description page of Project Settings.


#include "EatableObjects.h"
#include "Components/BoxComponent.h"
#include "SweetiephantsCharacter.h"
#include "PaperSpriteComponent.h"

AEatableObjects::AEatableObjects()
{
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;
}

void AEatableObjects::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AEatableObjects::OnOverlapBegin);


	ShownSprite = Cast<UPaperSpriteComponent>(GetComponentByClass(UPaperSpriteComponent::StaticClass()));
	
	if (ShownSprite)
	{
		ShownSprite->SetSprite(Sprite[FMath::RandRange(0, 2)]);
	}
}

void AEatableObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FloatObject(DeltaTime);
}

void AEatableObjects::FloatObject(float DeltaTime)
{
	NewLocation = this->GetActorLocation();
	DeltaHight = (FMath::Sin((ExecutionTime + DeltaTime) * FloatingSpeed) - FMath::Sin(ExecutionTime * FloatingSpeed));
	NewLocation.Z += DeltaHight * FloatingGap;
	ExecutionTime += DeltaTime;

	this->SetActorLocation(NewLocation);
}

void AEatableObjects::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor->IsA<ASweetiephantsCharacter>())
	{
		Destroy();
	}
}

bool AEatableObjects::GetIsToxic() const
{
	return bIsToxic;
}

