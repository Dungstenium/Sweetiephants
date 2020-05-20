// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreCounter.h"
#include "GameFramework/PlayerController.h" 
#include "Engine/World.h" 
#include "SweetiephantsCharacter.h"

UScoreCounter::UScoreCounter()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UScoreCounter::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ASweetiephantsCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	
	if (Player)
	{
		OldScorePoints = Player->GetScore();
	}
}

void UScoreCounter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Player)
	{
		if (Player->GetScore() != OldScorePoints)
		{
			OldScorePoints = Player->GetScore();
			UE_LOG(LogTemp, Warning, TEXT("%i"), OldScorePoints);
		}
	}
}

