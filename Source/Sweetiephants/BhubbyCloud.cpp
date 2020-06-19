// Fill out your copyright notice in the Description page of Project Settings.


#include "BhubbyCloud.h"
#include "PaperFlipbookComponent.h"


ABhubbyCloud::ABhubbyCloud()
{
	PrimaryActorTick.bCanEverTick = false;

	ChubbyCloudVFX = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Cloud"));
	RootComponent = ChubbyCloudVFX;
}

void ABhubbyCloud::BeginPlay()
{
	Super::BeginPlay();
	
	ChubbyCloudVFX->SetLooping(false);
	ChubbyCloudVFX->PlayFromStart();
	SetLifeSpan(ChubbyCloudVFX->GetFlipbookLength());
}


