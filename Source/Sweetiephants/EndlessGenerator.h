// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndlessGenerator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWEETIEPHANTS_API UEndlessGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEndlessGenerator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* Trigger;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
							AActor* OtherActor,
							UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex,
							bool bFromSweep, const
							FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		class ABackgroundClouds* Cloud;

	UPROPERTY(EditAnywhere)
		FVector Offset;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
