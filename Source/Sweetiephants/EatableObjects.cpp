// Fill out your copyright notice in the Description page of Project Settings.


#include "EatableObjects.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h" 
#include "Engine/TextRenderActor.h" 
#include "Engine/Font.h" 
#include "Kismet/GameplayStatics.h"
#include "PaperSpriteComponent.h"
#include "UObject/ConstructorHelpers.h" 
#include "SweetiephantsCharacter.h"


AEatableObjects::AEatableObjects()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;
}

void AEatableObjects::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AEatableObjects::OnOverlapBegin);

	StartPosition = GetActorLocation();

	ShownSprite = Cast<UPaperSpriteComponent>(GetComponentByClass(UPaperSpriteComponent::StaticClass()));
	
	if (ShownSprite)
	{
		ShownSprite->SetSprite(Sprite[FMath::RandRange(0, NumberOfSprites)]);
	}
}

void AEatableObjects::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor->IsA<ASweetiephantsCharacter>())
	{
		SetActorLocation(FVector(GetActorLocation().X - EatenOffset, GetActorLocation().Y, GetActorLocation().Z));

		if (EatenSound)
		{
			float RandomPitch = FMath::RandRange(0.85f, 1.15f);
			UGameplayStatics::PlaySound2D(this, EatenSound, 1.0f, RandomPitch);
		}
	}
}

bool AEatableObjects::GetIsToxic() const
{
	return bIsToxic;
}

void AEatableObjects::ResetPosition()
{
	if (Trigger)
	{
		Trigger->SetWorldLocation(StartPosition);
	}
}

void AEatableObjects::RenewSprite()
{
	if (ShownSprite)
	{
		ShownSprite->SetSprite(Sprite[FMath::RandRange(0, NumberOfSprites)]);
	}
}

