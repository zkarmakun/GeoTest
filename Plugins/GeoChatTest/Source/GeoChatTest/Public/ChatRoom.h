// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <UObject/NoExportTypes.h>
#include <MessageEndpoint.h>
#include "ChatRoom.generated.h"


class SDockTab;

USTRUCT()
struct FChatClientMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Chat")
		FString Message;

	UPROPERTY(EditAnywhere, Category = "Chat")
		FString FromUser;

	FChatClientMessage()
	{
		Message = FString();
		FromUser = FString();
	}

	FChatClientMessage(const FString& InMessage, const FString& InUser)
	{
		Message = InMessage;
		FromUser = InUser;
	}
};

USTRUCT()
struct FChatServerMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Chat")
		FString Message;

	UPROPERTY(EditAnywhere, Category = "Chat")
		FString FromUser;

	FChatServerMessage()
	{
		Message = FString();
		FromUser = FString();
	}

	FChatServerMessage(const FString& InMessage, const FString& InUser)
	{
		Message = InMessage;
		FromUser = InUser;
	}
};


/**
 * 
 */
class GEOCHATTEST_API FChatRoom
{
public:
	FChatRoom();
	~FChatRoom();

public:
	
	/**
	 * OpenChatWindow
	 
	 * @Param: User - Label for the chat, needs to be unique in the client list
	*/
	void OpenChatWindow(FName User);

	/* Close the chat room*/
	void CloseChatRoom();

private:
	/* Init the chat room with message bus*/
	void Init();

	/* Shutdown this chat room instance*/
	void Shutdown();


	/**
	 * HandleMessage Called when receive a message from a client
	 
	 * @Param: InMessage	- Message to be handle
	 * @Param: Context		- Message context
	*/
	void HandleMessage(const FChatClientMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);

	/**
	 * RegisterTabSpawner Register a new tab using the user name
	 
	 * @Param:  InUser - User name will be the tab name
	*/
	void RegisterTabSpawner(FName InUser);

	/* Unregister all possible chat tabs*/
	void UnregisterAllTabs();

	/**
	 * OnSpawnChatTab Called when we invoke a chat tab
	 
	 * @Param: SpawnTabArgs - Spawn tan arguments
	 * @Param: InUser		- user tab owner
	*/
	TSharedRef<SDockTab> OnSpawnChatTab(const FSpawnTabArgs& SpawnTabArgs, FName InUser);


private:
	/* List of clients*/
	TArray<FName> Clients;

	/* Server end point*/
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> Endpoint;
};

/* Useless class to have generated ustruct stuff*/
UCLASS()
class UChatDummyObject : public UObject
{
	GENERATED_BODY()

};