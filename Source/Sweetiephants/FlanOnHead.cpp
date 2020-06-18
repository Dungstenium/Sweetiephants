// Fill out your copyright notice in the Description page of Project Settings.


#include "FlanOnHead.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"


// Sets default values
AFlanOnHead::AFlanOnHead()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LooseFlan = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("TheFlan"));
	RootComponent = LooseFlan;
}

// Called when the game starts or when spawned
void AFlanOnHead::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlanOnHead::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Timer += DeltaSeconds;

	SetActorRelativeLocation(FVector(GetActorLocation().X - (250 - Timer * 70.0f) * DeltaSeconds, 0, (GetActorLocation().Z + (20 - Timer * 559.8f) * DeltaSeconds)));
	LooseFlan->AddLocalRotation(FRotator(0.4f, 0.0f, 0.0f));
}


