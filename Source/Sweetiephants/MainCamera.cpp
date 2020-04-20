// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Engine/World.h" 
#include "Components/BoxComponent.h" 
#include "SweetiephantsCharacter.h"
#include "GameFramework/PlayerController.h" 

AMainCamera::AMainCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	LowerTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Lower Trigger"));
	LowerTriggerBox->SetupAttachment(RootComponent);
}

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMainCamera::OnOverlapBegin);
	SetActorLocation(GetWorld()->GetFirstPlayerController()->GetTargetLocation() + Offset);
}

void AMainCamera::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<ASweetiephantsCharacter>())
	{
		UE_LOG(LogTemp, Warning, TEXT("dead"));
		bIsDead = true;
	}
}

void AMainCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetActorLocation(FVector(GetWorld()->GetFirstPlayerController()->GetPawn()->GetTargetLocation().X + Offset.X,
		2000.0f,
		GetActorLocation().Z));
}
