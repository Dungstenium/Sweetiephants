// Fill out your copyright notice in the Description page of Project Settings.


#include "ObkectFloater.h"
#include "GameFramework/Actor.h" 


UObkectFloater::UObkectFloater()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UObkectFloater::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	NewLocation = GetOwner()->GetActorLocation();
	DeltaHeight = (FMath::Sin((ExecutionTime + DeltaTime) * FloatingSpeed) - FMath::Sin(ExecutionTime * FloatingSpeed));
	NewLocation.Z += DeltaHeight * FloatingGap;
	ExecutionTime += DeltaTime;

	GetOwner()->SetActorLocation(NewLocation);
}

