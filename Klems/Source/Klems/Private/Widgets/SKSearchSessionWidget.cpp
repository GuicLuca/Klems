// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SKSearchSessionWidget.h"

void USKSearchSessionWidget::WorkOnSession(const FOTSessionSearchResult& session,int32 & ms,int32 & CurrentPlayer, int32 & MaxPlayers, FString & SessionName, FString & SessionId, bool & bIsPrivate, FString & Password)
{
	ms = session.PingInMs;
	CurrentPlayer = session.Session.SessionSettings.NumPublicConnections - session.Session.NumOpenPublicConnections;
	MaxPlayers = session.Session.SessionSettings.NumPublicConnections;
	SessionId = session.Session.GetSessionIdStr();
	session.Session.SessionSettings.Get(FName("IsPrivate"),bIsPrivate);
	session.Session.SessionSettings.Get(FName("SessionName"),SessionName);
	session.Session.SessionSettings.Get(FName("Password"),Password);

	
	
}

void USKSearchSessionWidget::TravelToLobby(FString LobbyMap)
{
	if(auto* World = GetWorld())
	{
		bool result = World->ServerTravel(LobbyMap.Append("?listen"));
		if(result)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("C++ travel ok"));	

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("C++ travel pas ok"));	

		}
	}
}