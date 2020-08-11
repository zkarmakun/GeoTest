// Fill out your copyright notice in the Description page of Project Settings.


#include "SChat.h"
#include "SlateOptMacros.h"
#include <Widgets/SBoxPanel.h>
#include <Widgets/Layout/SBox.h>
#include <Widgets/Layout/SBorder.h>
#include <Widgets/Input/SEditableTextBox.h>
#include <Widgets/Layout/SScrollBar.h>
#include <Widgets/Text/SMultiLineEditableText.h>
#include <Widgets/Input/SMultiLineEditableTextBox.h>
#include <Widgets/Layout/SGridPanel.h>
#include <Widgets/Layout/SScrollBox.h>
#include <Framework/Text/RichTextLayoutMarshaller.h>
#include <Framework/Text/RichTextMarkupProcessing.h>
#include "GeoChatTestStyle.h"
#include <Styling/SlateStyle.h>
#include <Styling/SlateTypes.h>

#define LOCTEXT_NAMESPACE "SChat"

SChat::~SChat()
{
	ChatClient.Shutdown();
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SChat::Construct(const FArguments& InArgs)
{
	User = InArgs._User;

	//~ Create marshaller
	TArray< TSharedRef< class ITextDecorator > > CreatedDecorators;
	TSharedRef<FRichTextLayoutMarshaller> Marshaller = FRichTextLayoutMarshaller::Create(
						FDefaultRichTextMarkupParser::GetStaticInstance(), 
						FDefaultRichTextMarkupWriter::Create(), 
						CreatedDecorators, 
						&FGeoChatTestStyle::Get());

	ChildSlot	
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		[
			SNew(SBox)
			.HeightOverride(20)
		]
		+ SVerticalBox::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SBorder)
			[
				SAssignNew(MultilineText, SMultiLineEditableTextBox)
				.Style(&FGeoChatTestStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("chatStyle"))
				.ForegroundColor(FLinearColor::Black)
				.IsReadOnly(true)
				.AlwaysShowScrollbars(true)
				.Marshaller(Marshaller)
			]
			
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(FMargin(0,10,0,0))
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(EditableText, SEditableTextBox)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Fill)
			.Padding(FMargin(10,0,0,0))
			[
				SNew(SButton)
				.Text(LOCTEXT("Chat", "Send"))
				.OnClicked(this, &SChat::SendMessage)
			]
		]
	];
	
	//~ Start chat client, sets the delegate to recv msgs
	ChatClient.Start(FOnChatMessageReceived::CreateRaw(this, &SChat::OnMessageRecv));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SChat::SendMessage()
{
	//~ If text is not empty we send a new message
	if (!EditableText->GetText().IsEmpty())
	{	
		ChatClient.SendMessage(EditableText->GetText().ToString(), User.ToString());
		EditableText->SetText(EmptyText);
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void SChat::AddMessageIntoText(const FString& InMessage, bool bSelf, FString OtherUser /*= "Other"*/)
{
	//~ create new text chuck using decorators for the marshaller, check the slate style FGeoChatTestStyle
	FString chunk = (bSelf) ? "<default>Me: " : "<others>" + OtherUser + ": ";
	chunk += InMessage + "</>\n";

	//~ Add new chuck to previous text
	FString Messages = MultilineText->GetText().ToString();
	Messages += chunk;

	MultilineText->SetText(FText::FromString(Messages));
}

void SChat::OnMessageRecv(const FChatServerMessage& InMessage)
{
	// When we recv a msg we check if is from self of other chat guy
	if (InMessage.FromUser == User.ToString())
	{
		AddMessageIntoText(InMessage.Message, true);
	}
	else
	{
		AddMessageIntoText(InMessage.Message, false, InMessage.FromUser);
	}
}

#undef LOCTEXT_NAMESPACE