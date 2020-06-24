// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

UCLASS()
class SWEETIEPHANTS_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	

	FVector StartPosition;

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

public:	
	ABaseEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Trigger;

	UFUNCTION(BlueprintCallable)
	void ResetPosition();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Sounds)
	class USoundBase* PlayerCrashSound;

};
