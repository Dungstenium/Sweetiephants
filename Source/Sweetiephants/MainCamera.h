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
	float Volume = 1.0f;

	UPROPERTY(EditAnywhere)
	FVector Offset;

	UPROPERTY(EditAnywhere)
	float CloudOffset;

	UPROPERTY()
	APawn* Camera;

	bool bSoundPlayed = false;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* LowerTriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* GeneratorTriggerBox;

	UPROPERTY(BlueprintReadWrite)
	bool bIsDead{ false };

	UPROPERTY(BlueprintReadWrite)
	bool bIsDeadDelayed{ false };

	UPROPERTY(BlueprintReadWrite)
	bool bIsOnDeathScreen{ false };

	UPROPERTY(BlueprintReadWrite)
	float ScaleX{ 0.0f };

	UPROPERTY(BlueprintReadWrite)
	float ScaleY{ 0.0f };

	UFUNCTION(BlueprintCallable)
	void Restart();

	UFUNCTION(BlueprintCallable)
	void MuteSound();

	UFUNCTION(BlueprintCallable)
	void UnmuteSound();

protected:

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
						AActor* OtherActor,
						UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex,
						bool bFromSweep, const
						FHitResult& SweepResult);

	UFUNCTION()
	void OnGeneratorOverlapBegin(UPrimitiveComponent* OverlappedComponent,
								AActor* OtherActor,
								UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex,
								bool bFromSweep, const
								FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = Sounds)
	class USoundBase* GameOverSound;

	void SetNewEnemySpawn(int32 Multiplier);

	void SetNewEatableSpawn(int32 Multiplier);

	void SetNewCloudSpawn();

	UPROPERTY()
	class ABackgroundClouds* Cloud;

	UPROPERTY()
	class AEatableObjects* Eatable;

	UPROPERTY()
	class ABaseEnemy* Enemy;

	FVector LastSpawnPosition;

	FTimerHandle Timer;

	UFUNCTION()
	void StopGameMovement();

	UPROPERTY(EditAnywhere)
	float Alpha{ 0.0f };

	UPROPERTY(EditAnywhere)
	float Exponent{ 0.0f };
};
