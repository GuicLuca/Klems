// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/KSLobbyGameMode.h"

#include "GameFramework/GameStateBase.h"

void AKSLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	if(NumberOfPlayers > 2)
	{
		auto* World = GetWorld();
		if(World)
		{
			bUseSeamlessTravel = true;
			World->ServerTravel(FString("/Game/Klems/Levels/Maps/LVL_Map1?listen"));
		}
	}
}
