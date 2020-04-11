// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BackgroundClouds.generated.h"

UCLASS()
class SWEETIEPHANTS_API ABackgroundClouds : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABackgroundClouds();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector ActorActualLocation;

	UPROPERTY(EditAnywhere, Category = Atributes)
	float MovingSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};