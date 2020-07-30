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
class UPaperFlipbook;
class UArrowComponent;
class UPaperFlipbookComponent;
class USoundBase;
class ABhubbyCloud;
class AFlanOnHead;

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

	void HandleMusic();

	void LoopMusic(USoundBase* MusicToBePlayed);

	void ManageVFX(const float& DeltaSeconds);

	void Die(const float& DeltaSeconds);

	void ManageElephantSize();

	void MorphElephant(const float& DeltaSeconds);

	void MorphToFat(const float& DeltaSeconds);
	//void MorphToSlim(float DeltaSeconds);
	void MorphToFit(const float& DeltaSeconds);

	float Timer{ 0.0f };
	float CloudVFXTimer{ 0.0f };
	float LinesVFXTimer{ 0.0f };
	float SweatVFXTimer{ 0.0f };
	float ExclamationVFXTimer{ 0.0f };
	float AfterDeathTimer{ 0.0f };
	float MorphTimer{ 0.0f };
	float GameSpeedTimer{ 0.0f };
	float TutTimer{ 0.0f };
	float ConfetiTimer{ 0.0f };

	float MorphingDuration = 1.0f;
	float StartingSpeed = 0.5f;
	float ActualSpeed = 0.5f;
	float SoundEffectsVolume = 1.3f;
	float MusicVolume = 0.5f;
	float ScaleX = 0.21f;
	float ScaleZ = 0.21f;
	float WalkSpeed = 600.0f;
	float TutorialColorOpacity{ 0 };

	bool bIsCloudActivated = false;
	bool bLinesActivated = false;
	bool bIsSweating = false;
	bool bIsExclamating = false;
	bool bIsDeadByHunger = false;
	bool bSpawnedFlan = false;
	bool bTutEnded = false;
	bool bIsMusicMuted = false;

	int32 Score{ 0 };

	FVector StartingPosition;

	UElephantWeight ElephantWeight;
	
	FTimerHandle MusicTimerHandle;

	UPROPERTY(EditAnywhere)
	UArrowComponent* GuideArrow;

	void Immobilize();

	void PlayInGameMusic();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* FitFlying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* FitTap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* FitIdle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* ChubbyIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* ChubbyFlying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* ChubbyTap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* MorphingToChubby;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* MorphingChubbyToFit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* MorphingToCraver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* CraverForm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* ChubbyDying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* FitDying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* ChubbyDyingFinal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* FitDyingFinal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* DeathEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* LinesVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* ExclamationVFX;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* CloudsVFX;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* SweatVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* ConfetiVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* TutorialImage;

	UPROPERTY(EditAnywhere, Category = SoundEffects) 
	USoundBase* MorphToChubbySound;

	UPROPERTY(EditAnywhere, Category = SoundEffects)
	USoundBase* MorphToFitSound;

	UPROPERTY(EditAnywhere, Category = SoundEffects)
	USoundBase* TapFitSound;

	UPROPERTY(EditAnywhere, Category = SoundEffects)
	USoundBase* TapChubbySound;

	UPROPERTY(EditAnywhere, Category = SoundEffects)
	USoundBase* SweatSound;

	UPROPERTY(EditAnywhere, Category = SoundEffects)
	USoundBase* DyingFromHungerSound;

	UPROPERTY(EditAnywhere, Category = Music)
	USoundBase* InGameMusic;

	UPROPERTY(EditAnywhere, Category = Music)
	USoundBase* MenuMusic;

	ABhubbyCloud* bhubby;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TSubclassOf<ABhubbyCloud> ChubbyCloud;

	virtual void BeginPlay() override;

	void UpdateAnimation();

	void MoveRight(const float Value);

	void UpdateCharacter();

	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	void Fly();

	bool bShouldStartFlying{ false };
	bool bPlayerTapped{ false };

	UPROPERTY(EditAnywhere)
	float MaxHungryPoints{ 100 };

	UPROPERTY(VisibleAnywhere)
	float ActualHungryPoints{ 60 };

	UPROPERTY(EditAnywhere)
	float PointsDepletionSpeed{ 2.0f };

	UPROPERTY(EditAnywhere, Category = PlayerJump)
	float JumpHeight{ 650.0f };

	UPROPERTY(EditAnywhere, Category = PlayerJump)
	float JumpHeightFit{ 650.0f };

	UPROPERTY(EditAnywhere, Category = PlayerJump)
	float JumpHeightFat{ 400.0f };	
	
	UPROPERTY(EditAnywhere, Category = PlayerJump)
	float JumpHeightSlim{ 800.0f };

	UPROPERTY(EditAnywhere)
	float PointsPerSweetie{ 5.0f };

public:
	ASweetiephantsCharacter();
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	void SetPlayerDied(const bool& Value);
	bool GetPlayerDied() const;

	void AddScore(const int32& Value);

	UFUNCTION(BlueprintCallable)
	void RestartGame();

	UFUNCTION(BlueprintCallable)
	int32 GetScore();
	
	UFUNCTION(BlueprintCallable)
	void MuteSoundEffects();

	UFUNCTION(BlueprintCallable)
	void UnmuteSoundEffects();

	UFUNCTION(BlueprintCallable)
	void MuteMusic();

	UFUNCTION(BlueprintCallable)
	void UnmuteMusic();

	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* GameMusic;

	UPROPERTY(BlueprintReadWrite)
	bool bGameStarted{ false };

	UPROPERTY(BlueprintReadWrite)
	bool bPlayerDeadDelayed{ false };

	UPROPERTY(BlueprintReadWrite)
	bool bEateSweetie{ false };

	UPROPERTY(BlueprintReadWrite)
	bool bEateToxic{ false };

	bool bHitTheBottomCollider{ false };
	bool bIsFristMusicLoop{ true };

	UPROPERTY(BlueprintReadWrite)
	bool bInGameMusicIsPlaying{ false };

	AFlanOnHead* Flanny;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFlanOnHead> Flan;

	UElephantState ElephantState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PercentHungryPoints{ 60.0f };
};
