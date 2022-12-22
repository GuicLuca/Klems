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

int32 AKSGameState::getFirst()
{
	int32 index = 0;
	int32 scoreMax = scores[0];
	for (int32 i = 0; i<4; i++)
	{
		if (scores[i] > scoreMax)
		{
			scoreMax = scores[i];
			index = i;
		}
	}
	return index;
}

int32 AKSGameState::getSecond()
{
	int32 first = getFirst();
	int32 fourth = getFourth();

	int32 toCompare1 = NULL;
	int32 toCompare2 = NULL;	

	for(int32 i = 0; i<4 ; i++)
	{
		if (i!=first && i!=fourth)
		{
			if(toCompare1==NULL)
			{
				toCompare1 = i;
			} else
			{
				toCompare2 = i;
			}
		}
	}

	if (scores[toCompare1] >= scores[toCompare2])
	{
		return toCompare1;
	} else
	{
		return toCompare2;
	}
}

int32 AKSGameState::getThird()
{
	int32 first = getFirst();
	int32 fourth = getFourth();

	int32 toCompare1 = NULL;
	int32 toCompare2 = NULL;	

	for(int32 i = 0; i<4 ; i++)
	{
		if (i!=first && i!=fourth)
		{
			if(toCompare1==NULL)
			{
				toCompare1 = i;
			} else
			{
				toCompare2 = i;
			}
		}
	}

	if (scores[toCompare1] <= scores[toCompare2])
	{
		return toCompare1;
	} else
	{
		return toCompare2;
	}
}

int32 AKSGameState::getFourth()
{
	int32 index = 0;
	int32 scoreMin = scores[0];
	for (int32 i = 0; i<4; i++)
	{
		if (scores[i] < scoreMin)
		{
			scoreMin = scores[i];
			index = i;
		}
	}
	return index;
}
