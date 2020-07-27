// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessBackground.h"
#include "Components/BoxComponent.h" 
#include "Components/ArrowComponent.h" 
#include "PaperSpriteComponent.h"
#include "SweetiephantsCharacter.h"
#include "Engine/World.h" 

AEndlessBackground::AEndlessBackground()
{
	PrimaryActorTick.bCanEverTick = false;

	Background = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Background"));
	RootComponent = Background;
}

void AEndlessBackground::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AEndlessBackground::OnOverlapBegin);
}

void AEndlessBackground::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<ASweetiephantsCharacter>())
	{
		if (NextBackground)
		{
			FActorSpawnParameters SpawnParams;

			GetWorld()->SpawnActor<AEndlessBackground>(NextBackground, GetTargetLocation() + Offset, Background->GetComponentRotation(), SpawnParams);
		}
	}
}
