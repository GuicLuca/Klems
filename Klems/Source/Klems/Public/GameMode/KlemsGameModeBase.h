// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KlemsGameModeBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class KLEMS_API AKlemsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void PlayerDie(APlayerController* noob);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> joueurs;
	
};
