// Fill out your copyright notice in the Description page of Project Settings.


#include "ScorePointsPopUp.h"
#include "Engine/TextRenderActor.h" 
#include "Components/TextRenderComponent.h" 


void AScorePointsPopUp::Tick(float DeltaTime)
{
	SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 1.0f));
	//GetTextRender()->TextRenderColor.A = 
}
