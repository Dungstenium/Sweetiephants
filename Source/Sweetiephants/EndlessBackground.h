// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessBackground.generated.h"

UCLASS()
class SWEETIEPHANTS_API AEndlessBackground : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndlessBackground();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere)
		class UPaperSpriteComponent* Background;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AEndlessBackground> NextBackground;
	
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		FVector Offset;

};
