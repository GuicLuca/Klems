// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/KSLobbyGameState.h"

void AKSLobbyGameState::setReady(APlayerController* PLayer, bool status)
{
	if(status)
	{
		// player want to be ready
		if(!PlayerReady.Contains(PLayer))
		{
			PlayerReady.Add(PLayer);
			OnPlayerChangeState.Broadcast();
		}
	}
	else
	{
		// Player is no more ready
		if(PlayerReady.Contains(PLayer))
		{
			PlayerReady.Remove(PLayer);
			OnPlayerChangeState.Broadcast();
		}
	}
}
