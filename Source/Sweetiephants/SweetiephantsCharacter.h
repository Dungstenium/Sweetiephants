// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "SweetiephantsCharacter.generated.h"


UENUM()
enum UElephantWeight
{
	Fat,
	Normal,
	Slim
};

class UTextRenderComponent;

/**
 * This class is the default character for Sweetiephants, and it is responsible for all
 * physical interaction between the player and the world.
 *
 * The capsule component (inherited from ACharacter) handles collision with the world
 * The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
 * The Sprite component (inherited from APaperCharacter) handles the visuals
 */
UCLASS(config=Game)
class ASweetiephantsCharacter : public APaperCharacter
{
	GENERATED_BODY()

	UTextRenderComponent* TextComponent;

	virtual void Tick(float DeltaSeconds) override;

	float Timer = 0.0f;
	float AfterDeathTimer = 0.0f;

	bool bPlayerDied = false;

	void Die();

	UElephantWeight ElephantWeight;

protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
		class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* TapAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IdleAnimation;

	virtual void BeginPlay() override;

	void UpdateAnimation();

	void MoveRight(float Value);

	void UpdateCharacter();

	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	void Fly();

	bool bShouldStartFlying = false;

	bool bPlayerTapped = false;

	UPROPERTY(EditAnywhere)
	float MaxHungryPoints{ 100 };

	UPROPERTY(VisibleAnywhere)
	float ActualHungryPoints{ 60 };

	UPROPERTY(EditAnywhere)
	float PointsDepletionSpeed{ 2.0f };

	UPROPERTY(EditAnywhere)
	float JumpHeight{ 1000.0f };

	UPROPERTY(EditAnywhere)
	float PointsPerSweetie{ 5.0f };

public:
	ASweetiephantsCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PercentHungryPoints{ 60.0f };

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	void SetPlayerDied(bool Value);
	bool GetPlayerDied() const;

	UPROPERTY(BlueprintReadWrite)
	bool bGameStarted{ false };
};
