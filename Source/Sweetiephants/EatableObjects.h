// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EatableObjects.generated.h"

UCLASS()
class SWEETIEPHANTS_API AEatableObjects : public AActor
{
	GENERATED_BODY()


	FVector StartPosition;

	float SoundVolume = 1.0f;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Sprites)
		class UPaperSprite* Sprite[8];

	int NumberOfSprites = 7;

	UPROPERTY()
	class UPaperSpriteComponent* ShownSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = Sounds)
	class USoundBase* EatenSound;

	UPROPERTY(EditAnywhere)
	bool bIsToxic{ false };

	UPROPERTY(EditAnywhere)
	float EatenOffset{ 700.0f };

public:	
	AEatableObjects();

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		bool GetIsToxic() const;

	UFUNCTION(BlueprintCallable)
	void ResetPosition();

	void RenewSprite();

	UFUNCTION(BlueprintCallable)
	void MuteSound();

	UFUNCTION(BlueprintCallable)
	void UnmuteSound();
};
