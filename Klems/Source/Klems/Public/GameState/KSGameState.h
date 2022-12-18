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
	void EndRound(APlayerController* winner);

	UFUNCTION(BlueprintCallable)
	void StartRound();

	UFUNCTION(BlueprintCallable)
	TMap<APlayerController* , int32> EndGame();

protected:
	UPROPERTY(BlueprintReadOnly)
	TMap<APlayerController* , int32> scores;

	UPROPERTY(BlueprintReadWrite)
	int32 nbRound;

	UPROPERTY(BlueprintReadOnly)
	int32 numRound = 0;
};
