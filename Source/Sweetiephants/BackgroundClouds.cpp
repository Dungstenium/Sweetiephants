// Fill out your copyright notice in the Description page of Project Settings.


#include "BackgroundClouds.h"

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

	ActorActualLocation = GetActorLocation();
}

// Called every frame
void ABackgroundClouds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActorActualLocation.X -= MovingSpeed;
	this->SetActorLocation(ActorActualLocation);
}

