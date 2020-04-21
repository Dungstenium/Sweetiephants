// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Components/BoxComponent.h" 
#include "Engine/World.h" 
#include "GameFramework/PlayerController.h" 
#include "Kismet/GameplayStatics.h"
#include "SweetiephantsCharacter.h"
#include "TimerManager.h"

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

void AMainCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetActorLocation(FVector(GetWorld()->GetFirstPlayerController()->GetPawn()->GetTargetLocation().X + Offset.X,
		2000.0f,
		GetActorLocation().Z));

}

void AMainCamera::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<ASweetiephantsCharacter>())
	{
		ASweetiephantsCharacter* Player = Cast<ASweetiephantsCharacter>(OtherActor);

		bIsDead = true;

		GetWorldTimerManager().SetTimer(Timer, this, &AMainCamera::StopGameMovement, 1.2f, false);
	}
}

void AMainCamera::StopGameMovement()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);

	GetWorldTimerManager().ClearTimer(Timer);
}
