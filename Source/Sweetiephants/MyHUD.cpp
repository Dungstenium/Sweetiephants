// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Engine/Canvas.h" 


AMyHUD::AMyHUD()
{
	ConfetiVFX = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("ConfetiEffect"));
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	FVector2D Center(Canvas->ClipX * 0.9f, Canvas->ClipY * 0.2f);
	ConfetiVFX->SetRelativeLocation(FVector(Canvas->ClipX * 0.9f, 100.0f, Canvas->ClipY * 0.2f));
}
