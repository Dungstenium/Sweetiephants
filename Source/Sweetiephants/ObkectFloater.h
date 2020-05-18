// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObkectFloater.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWEETIEPHANTS_API UObkectFloater : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObkectFloater();

protected:
	UPROPERTY(EditAnywhere, Category = Atributes)
		float FloatingGap{ 120.0f };

	UPROPERTY(EditAnywhere, Category = Atributes)
		float FloatingSpeed{ 5.0f };

	float ExecutionTime{ 0.0f };
	float DeltaHeight{ 0.0f };
	FVector NewLocation{ 0.0f, 0.0f, 0.0f };

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
