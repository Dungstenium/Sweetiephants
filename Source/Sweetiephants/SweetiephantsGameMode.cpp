// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SweetiephantsGameMode.h"
#include "SweetiephantsCharacter.h"

ASweetiephantsGameMode::ASweetiephantsGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ASweetiephantsCharacter::StaticClass();	
}
