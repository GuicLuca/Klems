// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/KSGameState.h"

	

void AKSGameState::EndRound(APlayerController* winner)
{
	int32 score = scores[winner];
	score++;
	scores.Emplace(winner, score);	

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

TMap<APlayerController*, int32> AKSGameState::EndGame()
{
	return scores;
}
