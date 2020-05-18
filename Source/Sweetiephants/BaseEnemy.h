// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

UCLASS()
class SWEETIEPHANTS_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

public:	
	ABaseEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* Trigger;

protected:
	virtual void BeginPlay() override;
};
