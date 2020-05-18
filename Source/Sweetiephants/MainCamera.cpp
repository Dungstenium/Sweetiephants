// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Components/BoxComponent.h" 
#include "BackgroundClouds.h"
#include "BaseEnemy.h"
#include "EatableObjects.h"
#include "Engine/World.h" 
#include "GameFramework/PlayerController.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SweetiephantsCharacter.h"
#include "TimerManager.h"

AMainCamera::AMainCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	LowerTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Lower Trigger"));
	LowerTriggerBox->SetupAttachment(RootComponent);

	GeneratorTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Generator Trigger"));
	GeneratorTriggerBox->SetupAttachment(RootComponent);
}

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	if (GeneratorTriggerBox && LowerTriggerBox)
	{
		LowerTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCamera::OnOverlapBegin);
		GeneratorTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCamera::OnGeneratorOverlapBegin);
	}

	SetActorLocation(GetWorld()->GetFirstPlayerController()->GetTargetLocation() + Offset);

	Camera = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void AMainCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetActorLocation(FVector(Camera->GetActorLocation().X + Offset.X,
		2000.0f,
		GetActorLocation().Z));

	if (bIsDeadDelayed)
	{
		if (ScaleX <= 1.0f)
		{
			ScaleX = FMath::InterpEaseInOut(ScaleX, 0.85f, Alpha, Exponent);
			ScaleY = FMath::InterpEaseInOut(ScaleY, 0.85f, Alpha, Exponent);
		}
	}
}

void AMainCamera::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
								AActor* OtherActor,
								UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex,
								bool bFromSweep, const
								FHitResult& SweepResult)
{
	if (OtherActor->IsA<ASweetiephantsCharacter>())
	{
		ASweetiephantsCharacter* Player = Cast<ASweetiephantsCharacter>(OtherActor);
		Player->GetCharacterMovement()->DisableMovement();

		bIsDead = true;

		GetWorldTimerManager().SetTimer(Timer, this, &AMainCamera::StopGameMovement, 1.2f, false);
	}
}

void AMainCamera::OnGeneratorOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ABackgroundClouds>())
	{
		Cloud = Cast<ABackgroundClouds>(OtherActor);

		if (Cloud)
		{
			FVector SpawnPosition;
			SpawnPosition = FVector(
				Cloud->GetActorLocation().X + CloudOffset,
				Cloud->GetActorLocation().Y,
				GetActorLocation().Z + FMath::RandRange(-300.0f, 500.0f));
			
			Cloud->SetActorLocation(SpawnPosition);

			float RandVariable = FMath::RandRange(1.0f, 3.0f);
			Cloud->SetMovingSpeed(RandVariable);
			Cloud->SetActorScale3D(FVector(RandVariable / 3.0f, RandVariable / 3.0f, RandVariable / 3.0f));
		}
	}
	else if (OtherActor->IsA<AEatableObjects>())
	{
		Eatable = Cast<AEatableObjects>(OtherActor);

		if (Eatable)
		{
			FVector EatableSpawnPosition;
			EatableSpawnPosition = FVector(
				Eatable->GetActorLocation().X + CloudOffset,
				Eatable->GetActorLocation().Y,
				GetActorLocation().Z + FMath::RandRange(-300.0f, 300.0f));

			UE_LOG(LogTemp, Warning, TEXT("%.2f and %.2f"), EatableSpawnPosition.X, LastSpawnPosition.X);
			if (FMath::Abs(EatableSpawnPosition.X - LastSpawnPosition.X) <= 300 || EatableSpawnPosition.X <= LastSpawnPosition.X)
			{
				if (EatableSpawnPosition.X >= LastSpawnPosition.X)
				{
					EatableSpawnPosition.X += 300;
				}
				else
				{
					EatableSpawnPosition.X = LastSpawnPosition.X + 300;
				}
			}

			LastSpawnPosition = EatableSpawnPosition;

			Eatable->SetActorLocation(EatableSpawnPosition);
		}
	}
	else if (OtherActor->IsA<ABaseEnemy>())
	{
		Enemy = Cast<ABaseEnemy>(OtherActor);

		if (Enemy)
		{
			FVector EnemySpawnPosition;
			EnemySpawnPosition = FVector(
				Enemy->GetActorLocation().X + CloudOffset,
				Enemy->GetActorLocation().Y,
				GetActorLocation().Z + FMath::RandRange(-300.0f, 500.0f));

			Enemy->SetActorLocation(EnemySpawnPosition);
		}
	}
}

void AMainCamera::StopGameMovement()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);


	bIsDeadDelayed = true;

	GetWorldTimerManager().ClearTimer(Timer);
}
