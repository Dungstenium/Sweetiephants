// Fill out your copyright notice in the Description page of Project Settings.


#include "FlanOnHead.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"


AFlanOnHead::AFlanOnHead()
{
	PrimaryActorTick.bCanEverTick = true;

	LooseFlan = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("TheFlan"));
	RootComponent = LooseFlan;
}

void AFlanOnHead::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(5.0f);
}

void AFlanOnHead::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Timer += DeltaSeconds;

	SetActorRelativeLocation(FVector(GetActorLocation().X - (250 - Timer * 70.0f) * DeltaSeconds, 0, (GetActorLocation().Z + (20 - Timer * 559.8f) * DeltaSeconds)));
	LooseFlan->AddLocalRotation(FRotator(0.4f, 0.0f, 0.0f));
}


