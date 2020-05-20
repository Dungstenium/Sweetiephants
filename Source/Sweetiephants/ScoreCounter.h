// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreCounter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWEETIEPHANTS_API UScoreCounter : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class ASweetiephantsCharacter* Player;

	int32 OldScorePoints = 0;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UScoreCounter();
		
};
