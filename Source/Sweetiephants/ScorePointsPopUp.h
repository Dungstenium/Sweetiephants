// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TextRenderActor.h"
#include "ScorePointsPopUp.generated.h"

/**
 * 
 */
UCLASS()
class SWEETIEPHANTS_API AScorePointsPopUp : public ATextRenderActor
{
	GENERATED_BODY()


	virtual void Tick(float DeltaTime) override;
};
