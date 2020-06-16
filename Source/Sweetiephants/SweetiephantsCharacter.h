// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "SweetiephantsCharacter.generated.h"


UENUM()
enum UElephantWeight
{
	Chubby,
	Fit
};

UENUM()
enum UElephantState
{
	Morphing,
	Normal,
	Dead,
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

	void Die(float DeltaSeconds);

	void ManageElephantSize();

	void MorphElephant(float DeltaSeconds);

	void MorphToFat(float DeltaSeconds);
	//void MorphToSlim(float DeltaSeconds);
	void MorphToFit(float DeltaSeconds);

	float Timer = 0.0f;
	float CloudVFXTimer = 0.0f;
	float LinesVFXTimer = 0.0f;
	float SweatVFXTimer = 0.0f;
	float ExclamationVFXTimer = 0.0f;
	float AfterDeathTimer = 0.0f;
	float MorphTimer = 0.0f;
	float MorphingDuration = 1.0f;
	float GameSpeedTimer = 0.0f;
	float StartingSpeed = 0.5f;
	float ActualSpeed = 0.5f;

	bool bIsCloudActivated = false;
	bool bLinesActivated = false;
	bool bIsSweating = false;
	bool bIsExclamating = false;
	bool bIsDeadByHunger = false;

	int32 Score = 0;

	FVector StartingPosition;

	void Immobilize();

	UElephantWeight ElephantWeight;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
		class UPaperFlipbook* FitFlying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* FitTap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* FitIdle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* ChubbyIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* ChubbyFlying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* ChubbyTap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* MorphingToChubby;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* MorphingChubbyToFit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* MorphingToCraver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* CraverForm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbookComponent* DeathEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbookComponent* LinesVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbookComponent* ExclamationVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbookComponent* CloudsVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbookComponent* SweatVFX;

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

	UPROPERTY(EditAnywhere, Category = Jump)
	float JumpHeight{ 650.0f };

	UPROPERTY(EditAnywhere, Category = Jump)
	float JumpHeightFit{ 650.0f };

	UPROPERTY(EditAnywhere, Category = Jump)
	float JumpHeightFat{ 400.0f };	
	
	UPROPERTY(EditAnywhere, Category = Jump)
	float JumpHeightSlim{ 800.0f };

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

	void AddScore(int32 Value);

	UFUNCTION(BlueprintCallable)
	int32 GetScore();
	
	UPROPERTY(BlueprintReadWrite)
	bool bGameStarted{ false };

	UPROPERTY(BlueprintReadWrite)
	bool bPlayerDeadDelayed = false;

	UElephantState ElephantState;

	UFUNCTION(BlueprintCallable)
	void RestartGame();

};
