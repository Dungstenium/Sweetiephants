// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EatableObjects.generated.h"

UCLASS()
class SWEETIEPHANTS_API AEatableObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	AEatableObjects();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Sprites)
		class UPaperSprite* Sprite[3];

	UPROPERTY()
		class UPaperSpriteComponent* ShownSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = Atributes)
		float FloatingGap{ 120.0f };

	UPROPERTY(EditAnywhere, Category = Atributes)
		float FloatingSpeed{ 5.0f };

	UPROPERTY(EditAnywhere)
		bool bIsToxic{ false };
public:	
	virtual void Tick(float DeltaTime) override;

	void FloatObject(float DeltaTime);

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		bool GetIsToxic() const;
private:

	float ExecutionTime { 0.0f };
	float DeltaHight { 0.0f };
	FVector NewLocation { 0.0f, 0.0f, 0.0f };
};
