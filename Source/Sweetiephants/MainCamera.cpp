// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Engine/World.h" 
#include "GameFramework/PlayerController.h" 

AMainCamera::AMainCamera()
{
	//Player = GetWorld()->GetFirstPlayerController();
}

void AMainCamera::BeginPlay()
{
	SetActorLocation(GetWorld()->GetFirstPlayerController()->GetTargetLocation() + Offset);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetWorld()->GetFirstPlayerController()->GetTargetLocation().ToString());
}

void AMainCamera::Tick(float DeltaSeconds)
{
	//SetActorLocation(FVector 
		//(FMath::InterpEaseInOut(GetActorLocation().X, GetWorld()->GetFirstPlayerController()->GetTargetLocation().X, .5f, 1.0f),
		//10.0f,
		//GetActorLocation().Z));
}
