// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/KSLobbyGameState.h"

#include "Engine/ActorChannel.h"

bool AKSLobbyGameState::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool result = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for(auto* PlayerCtrl : PlayerReady)
	{
		if(!PlayerCtrl) continue;
		result |= Channel->ReplicateSubobject(PlayerCtrl, *Bunch, *RepFlags);
	}
	return result;
}

int32 AKSLobbyGameState::GetAmoutOfReadyPLayer() const
{
	return PlayerReady.Num();
}

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

bool AKSLobbyGameState::IsReady(APlayerController* Player)
{
	return PlayerReady.Contains(Player);
}
