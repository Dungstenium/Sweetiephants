// Fill out your copyright notice in the Description page of Project Settings.


#include "EatableObjects.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h" 
#include "Engine/TextRenderActor.h" 
#include "PaperSpriteComponent.h"
#include "SweetiephantsCharacter.h"


AEatableObjects::AEatableObjects()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;

	//ScorePointPopUp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScorePoints"));
	//ScorePointPopUp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(0.0f, 0.0f, 90.0f));
}

void AEatableObjects::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AEatableObjects::OnOverlapBegin);


	ShownSprite = Cast<UPaperSpriteComponent>(GetComponentByClass(UPaperSpriteComponent::StaticClass()));
	
	if (ShownSprite)
	{
		ShownSprite->SetSprite(Sprite[FMath::RandRange(0, 2)]);
	}
}

void AEatableObjects::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor->IsA<ASweetiephantsCharacter>())
	{
		ATextRenderActor* ScorePoints = GetWorld()->SpawnActor<ATextRenderActor>(
			GetActorLocation() + FVector(0.0f, 0.0f, 50.0f),
			GetActorRotation() + FRotator(0.0f, 90.0f, 0.0f));

		ScorePoints->GetTextRender()->SetText(TEXT("10"));
		ScorePoints->GetTextRender()->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));

		SetActorLocation(FVector(GetActorLocation().X - EatenOffset, GetActorLocation().Y, GetActorLocation().Z));
	}
}

bool AEatableObjects::GetIsToxic() const
{
	return bIsToxic;
}

