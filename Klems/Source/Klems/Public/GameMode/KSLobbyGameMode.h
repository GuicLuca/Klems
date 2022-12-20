// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UObject/Object.h"
#include "KSLobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KLEMS_API AKSLobbyGameMode : public AGameModeBase
{
public:
	AKSLobbyGameMode();

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	virtual void StartGame();
	
	
	GENERATED_BODY()
};
