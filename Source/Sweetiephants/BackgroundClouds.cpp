// Fill out your copyright notice in the Description page of Project Settings.


#include "BackgroundClouds.h"
#include "PaperSpriteComponent.h"

ABackgroundClouds::ABackgroundClouds()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABackgroundClouds::BeginPlay()
{
	Super::BeginPlay();

	ActorNewLocation = GetActorLocation();
	StartingPosition = ActorNewLocation;

	ShownSprite = Cast<UPaperSpriteComponent>(GetComponentByClass(UPaperSpriteComponent::StaticClass()));

	SetNewSprite();
}

void ABackgroundClouds::SetNewSprite()
{
	if (ShownSprite)
	{
		ShownSprite->SetSprite(CloudSprite[FMath::RandRange(0, 7)]);
	}
}

void ABackgroundClouds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActorNewLocation = GetActorLocation();
	ActorNewLocation.X -= MovingSpeed;
	SetActorLocation(ActorNewLocation);
}

float ABackgroundClouds::GetMovingSpeed()
{
	return MovingSpeed;
}

void ABackgroundClouds::SetMovingSpeed(const float& Value)
{
	MovingSpeed = Value;
}

void ABackgroundClouds::Reset()
{
	SetActorLocation(StartingPosition);
}

