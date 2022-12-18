// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KSGameState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class KLEMS_API AKSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void EndRound(FString winner);

	UFUNCTION(BlueprintCallable)
	void StartRound();

	UFUNCTION(BlueprintCallable)
	TArray<int32> EndGame();

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> scores;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> Players;

	UPROPERTY(BlueprintReadWrite)
	int32 nbRound;

	UPROPERTY(BlueprintReadWrite)
	int32 numRound = 0;
};
