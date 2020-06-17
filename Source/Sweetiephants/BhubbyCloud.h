// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BhubbyCloud.generated.h"

UCLASS()
class SWEETIEPHANTS_API ABhubbyCloud : public AActor
{
	GENERATED_BODY()
	
public:	
	ABhubbyCloud();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UPaperFlipbookComponent* ChubbyCloudVFX;
};
