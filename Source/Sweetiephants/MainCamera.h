// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MainCamera.generated.h"

/**
 * 
 */
UCLASS()
class SWEETIEPHANTS_API AMainCamera : public ACameraActor
{
	GENERATED_BODY()
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	AMainCamera();

	float PlayerPositionX;

	UPROPERTY(EditAnywhere)
	FVector Offset;
};
