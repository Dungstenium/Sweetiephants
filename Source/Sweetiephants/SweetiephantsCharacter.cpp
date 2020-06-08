// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SweetiephantsCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "MainCamera.h"
#include "EatableObjects.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// ASweetiephantsCharacter

ASweetiephantsCharacter::ASweetiephantsCharacter()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	RootComponent = GetCapsuleComponent();

	GetCharacterMovement()->bOrientRotationToMovement = false;

	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;


	LinesVFX = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("LINESVFX"));
	LinesVFX->SetVisibility(false);
	LinesVFX->SetupAttachment(RootComponent);

	DeathEffect = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("DeathVisualFX"));
	DeathEffect->SetVisibility(false);
	DeathEffect->SetupAttachment(RootComponent);

	ExclamationVFX = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("EXCLAMATIONVFX"));
	ExclamationVFX->SetVisibility(false);
	ExclamationVFX->SetupAttachment(RootComponent);

	SweatVFX = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SWEATVFX"));
	SweatVFX->SetVisibility(false);
	SweatVFX->SetupAttachment(RootComponent);

	CloudsVFX = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("CLOUDVFX"));
	CloudsVFX->SetVisibility(false);
	CloudsVFX->SetupAttachment(RootComponent);

	ElephantWeight = UElephantWeight::Fit;
	ElephantState = UElephantState::Normal;
}

void ASweetiephantsCharacter::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<AEatableObjects>())
	{
		AEatableObjects* EatableObject = Cast<AEatableObjects>(OtherActor);

		if (EatableObject->GetIsToxic())
		{
			ActualHungryPoints -= PointsPerSweetie;
			AddScore(-5);
		}
		else
		{
			ActualHungryPoints += PointsPerSweetie;
			AddScore(10);
		}

		ActualHungryPoints = FMath::Clamp(ActualHungryPoints, 0.0f, 100.0f);
	}
}

void ASweetiephantsCharacter::BeginPlay()
{
	Super::BeginPlay();

	AfterDeathTimer = 0.0f;
	bGameStarted = false;

	PercentHungryPoints = ActualHungryPoints / MaxHungryPoints;

	OnActorBeginOverlap.AddDynamic(this, &ASweetiephantsCharacter::OnOverlapBegin);
}

void ASweetiephantsCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? FitFlying : FitIdle;

	// Are we moving or standing still?
	if (ElephantWeight == UElephantWeight::Fit && ElephantState == UElephantState::Normal)
	{
		DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? FitFlying : FitIdle;
	}
	else if(ElephantWeight == UElephantWeight::Chubby && ElephantState == UElephantState::Normal)
	{
		DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? ChubbyFlying : ChubbyIdle;
	}


	if (bPlayerTapped && Timer >= GetSprite()->GetFlipbookLength())
	{
		bPlayerTapped = false;
		Timer = 0;
	}
	else if (bPlayerTapped)
	{
		if (ElephantWeight == UElephantWeight::Fit && ElephantState == UElephantState::Normal)
		{
			DesiredAnimation = FitTap;
		}
		else if(ElephantWeight == UElephantWeight::Chubby && ElephantState == UElephantState::Normal)
		{
			DesiredAnimation = ChubbyTap;
		}
	}

	if (ElephantState == UElephantState::Morphing)
	{
		if (ElephantWeight == UElephantWeight::Fit)
		{
			DesiredAnimation = MorphingChubbyToFit;
		}
		else if (ElephantWeight == UElephantWeight::Chubby)
		{
			DesiredAnimation = MorphingToChubby;
		}
	}

	if( GetSprite()->GetFlipbook() != DesiredAnimation 	)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void ASweetiephantsCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UpdateCharacter();

	if (bShouldStartFlying && ElephantState != UElephantState::Dead)
	{

		if (ElephantState != UElephantState::Morphing)
		{
			AddMovementInput(FVector(0.5f, 0.0f, 0.0f));

			ActualHungryPoints -= PointsDepletionSpeed * DeltaSeconds;
			PercentHungryPoints = FMath::FInterpTo(PercentHungryPoints, ActualHungryPoints / MaxHungryPoints, DeltaSeconds, 5);
		}
		else
		{
			MorphElephant(DeltaSeconds);
		}

		ManageElephantSize();
	
		if (bPlayerTapped)
		{
			Timer += DeltaSeconds;
		}

		if (bIsCloudActivated)
		{
			CloudVFXTimer += DeltaSeconds;
		}

		if (bLinesActivated)
		{
			LinesVFXTimer += DeltaSeconds;
		}

		if (CloudVFXTimer >= CloudsVFX->GetFlipbookLength())
		{
			CloudVFXTimer = 0.0f;
			CloudsVFX->SetVisibility(false);
			bIsCloudActivated = false;
		}

		if (LinesVFXTimer >= LinesVFX->GetFlipbookLength())
		{
			LinesVFXTimer = 0.0f;
			LinesVFX->SetVisibility(false);
			bLinesActivated = false;
		}
	}
	else if (ElephantState == UElephantState::Dead)
	{
		Die(DeltaSeconds);
	}
}

void ASweetiephantsCharacter::Die(float DeltaSeconds)
{
	if (AfterDeathTimer == 0.0f)
	{
		Immobilize();
		
		DeathEffect->SetVisibility(true);
		DeathEffect->PlayFromStart();
	}
	else if(AfterDeathTimer >= DeathEffect->GetFlipbookLength() && DeathEffect->IsVisible())
	{
		DeathEffect->SetVisibility(false);
	}
	else if (AfterDeathTimer >= 1 && GetCharacterMovement()->GravityScale != 1.0f)
	{
		GetCharacterMovement()->GravityScale = 1.0f;
	}

	AfterDeathTimer += DeltaSeconds;
}

void ASweetiephantsCharacter::MorphElephant(float DeltaSeconds)
{
	if (ElephantState == UElephantState::Morphing && ElephantWeight == UElephantWeight::Chubby)
	{
		MorphToFat(DeltaSeconds);
	}
	//else if (ElephantState == UElephantState::Morphing && ElephantWeight == UElephantWeight::Slim)
	//{
	//	MorphToSlim(DeltaSeconds);
	//}
	else if (ElephantState == UElephantState::Morphing && ElephantWeight == UElephantWeight::Fit)
	{
		MorphToFit(DeltaSeconds);
	}
}

void ASweetiephantsCharacter::MorphToFat(float DeltaSeconds)
{
	if (MorphTimer == 0.0f)
	{
		Immobilize();
	}

	MorphTimer += DeltaSeconds;

	if (MorphTimer >= 1.0f)
	{
		ElephantState = UElephantState::Normal;
		GetCharacterMovement()->GravityScale = 1.3f;
		MorphTimer = 0.0f;
		bPlayerTapped = false;
		JumpHeight = JumpHeightFat;
	}
}

//void ASweetiephantsCharacter::MorphToSlim(float DeltaSeconds)
//{
//	if (MorphTimer == 0.0f)
//	{
//		Immobilize();
//	}
//
//	MorphTimer += DeltaSeconds;
//
//	if (MorphTimer >= 1.0f)
//	{
//		ElephantState = UElephantState::Normal;
//		GetCharacterMovement()->GravityScale = 0.8f;
//		MorphTimer = 0.0f;
//		bPlayerTapped = false;
//		JumpHeight = JumpHeightSlim;
//	}
//}

void ASweetiephantsCharacter::MorphToFit(float DeltaSeconds)
{
	if (MorphTimer == 0.0f)
	{
		Immobilize();
	}

	MorphTimer += DeltaSeconds;

	if (MorphTimer >= 1.0f)
	{
		ElephantState = UElephantState::Normal;
		GetCharacterMovement()->GravityScale = 1.0f;
		MorphTimer = 0.0f;
		bPlayerTapped = false;
		JumpHeight = JumpHeightFit;
	}
}

void ASweetiephantsCharacter::ManageElephantSize()
{
	if (PercentHungryPoints >= 0.95f && ElephantWeight != UElephantWeight::Chubby)
	{
		ElephantWeight = UElephantWeight::Chubby;
		ElephantState = UElephantState::Morphing;
	}
	//else if (PercentHungryPoints <= 0.05f && ElephantWeight != UElephantWeight::Slim)
	//{
	//	ElephantWeight = UElephantWeight::Slim;
	//	ElephantState = UElephantState::Morphing;
	//}
	else if (PercentHungryPoints <= 0.5f && ElephantWeight == UElephantWeight::Chubby)
	{
		ElephantWeight = UElephantWeight::Fit;
		ElephantState = UElephantState::Morphing;
	}
}

void ASweetiephantsCharacter::Immobilize()
{
	GetMovementComponent()->StopMovementImmediately();
	GetCharacterMovement()->GravityScale = 0.0f;
}

void ASweetiephantsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASweetiephantsCharacter::Fly);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASweetiephantsCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ASweetiephantsCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ASweetiephantsCharacter::TouchStopped);
}

void ASweetiephantsCharacter::Fly()
{
	if (ElephantState != UElephantState::Dead && bGameStarted && ElephantState == UElephantState::Normal)
	{
		GetCharacterMovement()->Velocity.Z = JumpHeight;

		if (!bShouldStartFlying)
		{
			bShouldStartFlying = true;
		}

		bPlayerTapped = true;

		//CloudsVFX->SetRelativeLocation(FVector((0.0f, 0.0f, -151.0f)));
		if (ElephantWeight == UElephantWeight::Chubby)
		{
			CloudsVFX->SetVisibility(true);
			CloudsVFX->PlayFromStart();
			bIsCloudActivated = true;
			CloudVFXTimer = 0.0f;
		}

		LinesVFX->SetVisibility(true);
		LinesVFX->PlayFromStart();
		bLinesActivated = true;
		LinesVFXTimer = 0.0f;
	}
}

void ASweetiephantsCharacter::MoveRight(float Value)
{
	if (ElephantState != UElephantState::Dead)
	{
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
	}
}

void ASweetiephantsCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	Fly();
}

void ASweetiephantsCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	//bPlayerTapped = false;
}

void ASweetiephantsCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();	
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}

void ASweetiephantsCharacter::SetPlayerDied(bool bIsDead)
{
	if (bIsDead)
	{
		ElephantState = UElephantState::Dead;
	}
}

bool ASweetiephantsCharacter::GetPlayerDied() const
{
	if (ElephantState == UElephantState::Dead)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ASweetiephantsCharacter::AddScore(int32 Value)
{
	Score += Value;
}

int32 ASweetiephantsCharacter::GetScore()
{
	return Score;
}

