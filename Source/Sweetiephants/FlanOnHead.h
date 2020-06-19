// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlanOnHead.generated.h"

UCLASS()
class SWEETIEPHANTS_API AFlanOnHead : public AActor
{
	GENERATED_BODY()
	
public:	
	AFlanOnHead();

	float Timer = 0.0f;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	class UPaperFlipbookComponent* LooseFlan;
};
