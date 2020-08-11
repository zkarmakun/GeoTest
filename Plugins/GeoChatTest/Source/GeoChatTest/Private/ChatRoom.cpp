// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatRoom.h"
#include <Widgets/Docking/SDockTab.h>
#include "SChat.h"
#include <MessageEndpoint.h>

FChatRoom::FChatRoom()
{
	Init();
}

FChatRoom::~FChatRoom()
{
	UnregisterAllTabs();
}

void FChatRoom::OpenChatWindow(FName User)
{
	if (!Clients.Contains(User))
	{
		RegisterTabSpawner(User);
	}

	FGlobalTabmanager::Get()->InvokeTab(User);
}

void FChatRoom::CloseChatRoom()
{
	UnregisterAllTabs();
}

void FChatRoom::Init()
{
	Endpoint = FMessageEndpoint::Builder("EndpointName")
		.Handling<FChatClientMessage>(this, &FChatRoom::HandleMessage);

	if (Endpoint.IsValid())
	{
		Endpoint->Subscribe<FChatClientMessage>();
	}
}

void FChatRoom::Shutdown()
{
	Endpoint.Reset();
}

void FChatRoom::HandleMessage(const FChatClientMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)
{
	UE_LOG(LogTemp, Warning, TEXT("from: %s msg: %s"), *InMessage.FromUser, *InMessage.Message);

	if (Endpoint.IsValid())
		Endpoint->Publish(new FChatServerMessage(InMessage.Message, InMessage.FromUser));
}

void FChatRoom::RegisterTabSpawner(FName InUser)
{
	FText TabDisplayName = FText::FromString(InUser.ToString());
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(InUser, FOnSpawnTab::CreateRaw(this, &FChatRoom::OnSpawnChatTab, InUser))
		.SetDisplayName(TabDisplayName)
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FChatRoom::UnregisterAllTabs()
{
	for (auto& c : Clients)
	{
		FGlobalTabmanager::Get()->UnregisterTabSpawner(c);
	}
}

TSharedRef<SDockTab> FChatRoom::OnSpawnChatTab(const FSpawnTabArgs& SpawnTabArgs, FName InUser)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SChat)
			.User(InUser)
		];
}

