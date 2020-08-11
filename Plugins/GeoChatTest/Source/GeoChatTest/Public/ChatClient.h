// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MessageEndpoint.h>
#include "ChatRoom.h"

DECLARE_DELEGATE_OneParam(FOnChatMessageReceived, const FChatServerMessage&);

/**
 * 
 */
class GEOCHATTEST_API FChatClient
{

public:

	/**
	 * Start
	 
	 * @Param: InOnChatMessageReceived - Delegate to receive messages
	*/
	void Start(FOnChatMessageReceived InOnChatMessageReceived);

	//~ Shutdown chat
	void Shutdown();


	/**
	 * SendMessage to the chat room
	 
	 * @Param: Message  - Message to be send
	 * @Param: User		- User sending this message
	*/
	void SendMessage(const FString& Message, const FString& User);

private:

	/**
	 * HandleMessage Handle a message when is received
	 
	 * @Param: InMessage	- msg to be handled
	 * @Param: Context		- Msg context
	*/
	void HandleMessage(const FChatServerMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);
	
	
private:
	/* Client endpoint */
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> Endpoint;

	/* Delegate to receive msgs*/
	FOnChatMessageReceived OnChatMessageReceived;


};
