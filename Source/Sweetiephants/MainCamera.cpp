// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Engine/World.h" 
#include "GameFramework/PlayerController.h" 

AMainCamera::AMainCamera()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(GetWorld()->GetFirstPlayerController()->GetTargetLocation() + Offset);
}

void AMainCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetActorLocation(FVector(GetWorld()->GetFirstPlayerController()->GetPawn()->GetTargetLocation().X + Offset.X,
		2000.0f,
		GetActorLocation().Z));
}
