// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "ChatClient.h"

class SEditableTextBox;
class SScrollBar;
class SVerticalBox;
class SMultiLineEditableTextBox;

/**
 *	Create a simple chat UI using message bus
 */
class GEOCHATTEST_API SChat : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SChat)
	{}
	//~ Owner of this chat
	SLATE_ARGUMENT(FName, User)
	SLATE_END_ARGS()
	~SChat();

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	// Empty text to reset the editable text box
	FText EmptyText;

protected:
	// Reference to editable text box where we write the messages
	TSharedPtr<SEditableTextBox> EditableText;

	// Read only text box, here we print the messages list
	TSharedPtr<SMultiLineEditableTextBox> MultilineText;

	// Instance of chat client
	FChatClient ChatClient;

	// User name
	FName User;

protected:

	/* SendMessage Call from button to send a new message*/
	FReply SendMessage();

private:

	/**
	 * AddMessageIntoText Add a new text chunk to the text block
	 
	 * @Param: InMessage	- Message to be add to text block
	 * @Param: bSelf		- if that message was produce by the self user
	 * @Param: OtherUser	- Name of the sender
	*/
	void AddMessageIntoText(const FString& InMessage, bool bSelf, FString OtherUser = "Other");



	/**
	 * OnMessageRecv Call when receive message from server
	 
	 * @Param: InMessage - Message Received
	*/
	void OnMessageRecv(const FChatServerMessage& InMessage);
	
};
