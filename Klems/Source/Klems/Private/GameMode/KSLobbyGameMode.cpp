// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/KSLobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameState/KSLobbyGameState.h"

AKSLobbyGameMode::AKSLobbyGameMode()
{
	GameStateClass = AKSLobbyGameState::StaticClass();
}

void AKSLobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetGameState<AKSLobbyGameState>()->OnPlayerChangeState.AddDynamic(this,&AKSLobbyGameMode::StartGame);
}



void AKSLobbyGameMode::StartGame()
{
	const auto* gamestate = GetGameState<AKSLobbyGameState>();
	if(gamestate->PlayerArray.Num() == gamestate->PlayerReady.Num())
	{
		// Remove UI of LobbyPawn

		// Change to arena lvl
		if(auto* World = GetWorld())
		{
			bUseSeamlessTravel = true;
			World->ServerTravel(FString("/Game/Klems/Levels/Maps/LVL_Map1"));
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get the wordl in KSLobbyGameMode::StartGame"));
		}
	}
}


