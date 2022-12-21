// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/KSLobbyGameState.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

bool AKSLobbyGameState::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool Result = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for(auto* PlayerCtrl : PlayerReady)
	{
		if(!PlayerCtrl) continue;
		Result |= Channel->ReplicateSubobject(PlayerCtrl, *Bunch, *RepFlags);
	}
	return Result;
}

void AKSLobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AKSLobbyGameState,PlayerReady);
}

void AKSLobbyGameState::DebugLog() const
{
	for (auto PlayerController : PlayerReady)
	{
		auto Name = PlayerController->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Name);
	}
}

int32 AKSLobbyGameState::GetAmountOfReadyPLayer() const
{
	return PlayerReady.Num();
}

void AKSLobbyGameState::setReady(APlayerController* Player, bool status)
{
	if(status)
	{
		// player want to be ready
		if(!PlayerReady.Contains(Player))
		{
			PlayerReady.Add(Player);
			UE_LOG(LogTemp, Warning, TEXT("%s added to playerReady"), *Player->GetName());
			OnPlayerChangeState.Broadcast();
		}
	}
	else
	{
		// Player is no more ready
		if(PlayerReady.Contains(Player))
		{
			PlayerReady.Remove(Player);
			UE_LOG(LogTemp, Warning, TEXT("%s removed from playerReady"), *Player->GetName());
			OnPlayerChangeState.Broadcast();
		}
	}
}

bool AKSLobbyGameState::IsReady(APlayerController* Player)
{
	return PlayerReady.Contains(Player);
}
