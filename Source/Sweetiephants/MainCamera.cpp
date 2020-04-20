// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Engine/World.h" 
#include "GameFramework/PlayerController.h" 

AMainCamera::AMainCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	//Player = GetWorld()->GetFirstPlayerController();
}

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(GetWorld()->GetFirstPlayerController()->GetTargetLocation() + Offset);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetWorld()->GetFirstPlayerController()->GetTargetLocation().ToString());
}

void AMainCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetWorld()->GetFirstPlayerController()->GetPawn()->GetTargetLocation().ToString());

	SetActorLocation(FVector(GetWorld()->GetFirstPlayerController()->GetPawn()->GetTargetLocation().X,
		2000.0f,
		GetActorLocation().Z));


		//FVector(FMath::InterpEaseInOut(GetActorLocation().X, GetWorld()->GetFirstPlayerController()->GetTargetLocation().X, .5f, 1.0f)
}
