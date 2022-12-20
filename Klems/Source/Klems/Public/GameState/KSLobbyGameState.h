// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "UObject/Object.h"
#include "KSLobbyGameState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKSPLayerChangeStateDelegate);

UCLASS()

class KLEMS_API AKSLobbyGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	FKSPLayerChangeStateDelegate OnPlayerChangeState;

	UPROPERTY()
	TArray<APlayerController*> PlayerReady;

	/** Set the player status, if all player of the session are ready, the game will start */
	UFUNCTION(BlueprintCallable, Category="Player")
	void setReady(APlayerController* Player, bool status);

	
};
