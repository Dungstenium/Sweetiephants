// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/BoxComponent.h"
#include "SweetiephantsCharacter.h"


ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = GetActorLocation();

	OnActorBeginOverlap.AddDynamic(this, &ABaseEnemy::OnOverlapBegin);
}

void ABaseEnemy::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<ASweetiephantsCharacter>())
	{
		ASweetiephantsCharacter* Player = Cast<ASweetiephantsCharacter>(OtherActor);

		Player->SetPlayerDied(true);
	}
}

void ABaseEnemy::ResetPosition()
{
	if (Trigger)
	{
		Trigger->SetWorldLocation(StartPosition);
	}
}

