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
class KLEMS_API AKSLobbyGameMode : public AGameMode
{
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
private:
	GENERATED_BODY()
};
