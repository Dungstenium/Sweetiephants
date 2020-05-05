// Fill out your copyright notice in the Description page of Project Settings.


#include "BackgroundClouds.h"
#include "PaperSpriteComponent.h"

// Sets default values
ABackgroundClouds::ABackgroundClouds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABackgroundClouds::BeginPlay()
{
	Super::BeginPlay();

	ActorNewLocation = GetActorLocation();

	ShownSprite = Cast<UPaperSpriteComponent>(GetComponentByClass(UPaperSpriteComponent::StaticClass()));

	if (ShownSprite)
	{
		ShownSprite->SetSprite(Sprite[FMath::RandRange(0, 5)]);
	}
}

// Called every frame
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

void ABackgroundClouds::SetMovingSpeed(float Value)
{
	MovingSpeed = Value;
}

