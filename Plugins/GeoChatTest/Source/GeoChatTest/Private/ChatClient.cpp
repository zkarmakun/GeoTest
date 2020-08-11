// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatClient.h"
#include <MessageEndpoint.h>
#include "ChatRoom.h"
#include <MessageEndpointBuilder.h>

void FChatClient::Start(FOnChatMessageReceived InOnChatMessageReceived)
{
	OnChatMessageReceived = InOnChatMessageReceived;

	Endpoint = FMessageEndpoint::Builder("ChatEndPoint")
		.Handling<FChatServerMessage>(this, &FChatClient::HandleMessage)
		.Build();

	if (Endpoint.IsValid())
	{
		Endpoint->Subscribe<FChatServerMessage>();
	}
}

void FChatClient::Shutdown()
{
	Endpoint.Reset();
}

void FChatClient::SendMessage(const FString& Message, const FString& User)
{
	if (Endpoint.IsValid())
		Endpoint->Publish(new FChatClientMessage(Message, User));
}


void FChatClient::HandleMessage(const FChatServerMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)
{
	OnChatMessageReceived.ExecuteIfBound(InMessage);
}
