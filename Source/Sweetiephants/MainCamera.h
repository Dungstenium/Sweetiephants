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

	UPROPERTY()
		APawn* Camera;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* LowerTriggerBox;

	UPROPERTY(BlueprintReadWrite)
		bool bIsDead{ false };

	UPROPERTY(BlueprintReadWrite)
		bool bIsDeadDelayed{ false };

	UPROPERTY(BlueprintReadWrite)
		float ScaleX{ 0.0f };

	UPROPERTY(BlueprintReadWrite)
		float ScaleY{ 0.0f };

protected:

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	FTimerHandle Timer;

	UFUNCTION()
		void StopGameMovement();

	UPROPERTY(EditAnywhere)
		float Alpha{ 0.0f };

	UPROPERTY(EditAnywhere)
		float Exponent{ 0.0f };
};
