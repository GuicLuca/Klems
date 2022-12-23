// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sessions/OTSessionSearchResult.h"

#include "Blueprint/UserWidget.h"
#include "SKSearchSessionWidget.generated.h"

/**
 * 
 */
UCLASS()
class KLEMS_API USKSearchSessionWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void WorkOnSession(const FOTSessionSearchResult& session,int32 & ms,int32 & CurrentPlayer, int32 & MaxPlayers, FString & SessionName, FString & SessionId, bool & bIsPrivate, FString & Password);

	UFUNCTION(BlueprintCallable)
	void TravelToLobby(FString LobbyMap);
};
