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
}

void ASweetiephantsCharacter::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<AEatableObjects>())
	{
		AEatableObjects* EatableObject = Cast<AEatableObjects>(OtherActor);

		if (EatableObject->GetIsToxic())
		{
			ActualHungryPoints -= PointsPerSweetie;
		}
		else
		{
			ActualHungryPoints += PointsPerSweetie;
		}

		ActualHungryPoints = FMath::Clamp(ActualHungryPoints, 0.0f, 100.0f);
	}
}

void ASweetiephantsCharacter::BeginPlay()
{
	Super::BeginPlay();

	AfterDeathTimer = 0.0f;
	bGameStarted = false;

	OnActorBeginOverlap.AddDynamic(this, &ASweetiephantsCharacter::OnOverlapBegin);
}

void ASweetiephantsCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;


	if (bPlayerTapped && Timer >= GetSprite()->GetFlipbookLength())
	{
		bPlayerTapped = false;
		Timer = 0;
	}
	else if (bPlayerTapped)
	{
		DesiredAnimation = TapAnimation;
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

	if (bShouldStartFlying && !bPlayerDied)
	{
		AddMovementInput(FVector(0.5f, 0.0f, 0.0f));

		ActualHungryPoints -= PointsDepletionSpeed * DeltaSeconds;
		PercentHungryPoints = FMath::FInterpTo(PercentHungryPoints, ActualHungryPoints / MaxHungryPoints, DeltaSeconds, 5);

		if (bPlayerTapped)
		{
			Timer += DeltaSeconds;
		}
	}
	else if (bPlayerDied)
	{
		if (AfterDeathTimer == 0.0f)
			Die();

		AfterDeathTimer += DeltaSeconds;

		if (AfterDeathTimer >= 1 && AfterDeathTimer <= 2)
		{
			GetCharacterMovement()->GravityScale = 1.0f;
		}
	}
}

void ASweetiephantsCharacter::Die()
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
	if (!bPlayerDied && bGameStarted)
	{
		GetCharacterMovement()->Velocity.Z = JumpHight;

		if (!bShouldStartFlying)
		{
			bShouldStartFlying = true;
		}

		bPlayerTapped = true;
	}
}

void ASweetiephantsCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/
	if (!bPlayerDied)
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

void ASweetiephantsCharacter::SetPlayerDied(bool Value)
{
	bPlayerDied = Value;
}

bool ASweetiephantsCharacter::GetPlayerDied() const
{
	return bPlayerDied;
}

