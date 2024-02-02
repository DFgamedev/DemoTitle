// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChalesTributeGameMode.h"
#include "ChalesTributeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AChalesTributeGameMode::AChalesTributeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
