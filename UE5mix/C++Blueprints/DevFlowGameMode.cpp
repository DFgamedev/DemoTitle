// Copyright Epic Games, Inc. All Rights Reserved.

#include "DevFlowGameMode.h"
#include "DevFlowCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADevFlowGameMode::ADevFlowGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
