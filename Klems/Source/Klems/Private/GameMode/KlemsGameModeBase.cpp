// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameMode/KlemsGameModeBase.h"

void AKlemsGameModeBase::PlayerDie(APlayerController* noob)
{
	joueurs.Remove(noob);
}
