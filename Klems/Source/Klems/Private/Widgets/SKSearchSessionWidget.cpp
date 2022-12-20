// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SKSearchSessionWidget.h"

void USKSearchSessionWidget::WorkOnSession(const FOTSessionSearchResult& session,int32 & ms,int32 & CurrentPlayer, int32 & MaxPlayers, FString & SessionName, FString & SessionId, bool & bIsPrivate)
{
	ms = session.PingInMs;
	CurrentPlayer = session.Session.SessionSettings.NumPublicConnections - session.Session.NumOpenPublicConnections;
	CurrentPlayer = session.Session.SessionSettings.NumPublicConnections - session.Session.NumOpenPublicConnections;
	MaxPlayers = session.Session.SessionSettings.NumPublicConnections;
	SessionName = session.Session.OwningUserName;
	//session.Session.SessionSettings.Get(FName("IsPrivate"),bIsPrivate);
	SessionId = session.Session.GetSessionIdStr();
	
	
}