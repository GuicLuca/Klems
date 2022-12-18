// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/KSGameState.h"

	

void AKSGameState::EndRound(FString winner)
{
	int i = 0;
	for (FString player : Players)
	{
		if (player == winner)
		{
			scores[i]++;
		} else
		{
			i++;
		}
	}

	numRound++;
	StartRound();
}
void AKSGameState::StartRound()
{
	if (numRound<nbRound)
	{
		EndGame();
		return;
	}
}

TArray<int32> AKSGameState::EndGame()
{
	return scores;
}
