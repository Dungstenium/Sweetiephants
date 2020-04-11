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
	// Sets default values for this actor's properties
	AEatableObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = Atributes)
		float FloatingGap{ 120.0f };

	UPROPERTY(EditAnywhere, Category = Atributes)
		float FloatingSpeed{ 5.0f };

	UPROPERTY(EditAnywhere)
		bool bIsToxic{ false };
public:	
	// Called every frame
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
