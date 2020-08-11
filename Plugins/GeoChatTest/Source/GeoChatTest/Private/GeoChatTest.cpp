// Copyright Epic Games, Inc. All Rights Reserved.

#include "GeoChatTest.h"
#include "GeoChatTestStyle.h"
#include "GeoChatTestCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include <ToolMenuSection.h>
#include <Framework/SlateDelegates.h>
#include <Widgets/SBoxPanel.h>
#include "ChatRoom.h"
#include <Framework/Commands/UIAction.h>

static const FName GeoChatTestTabName("GeoChatTest");

#define LOCTEXT_NAMESPACE "FGeoChatTestModule"

void FGeoChatTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	ChatRoom = MakeShareable(new FChatRoom);

	FGeoChatTestStyle::Initialize();
	FGeoChatTestStyle::ReloadTextures();

	FGeoChatTestCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGeoChatTestModule::RegisterMenus));

	
}

void FGeoChatTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FGeoChatTestStyle::Shutdown();

	FGeoChatTestCommands::Unregister();
}

void FGeoChatTestModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			

		Section.AddEntry(FToolMenuEntry::InitComboButton(
			"Chat",
			FUIAction(),
			FOnGetContent::CreateRaw(this, &FGeoChatTestModule::GenerateChatMenuContent),
			LOCTEXT("Chat_Label", "Chat"),
			LOCTEXT("Chat_ToolTip", "Create cool chats"),
			FSlateIcon(FGeoChatTestStyle::GetStyleSetName(), "GeoChatTest.PluginAction")
		));
	}
}

TSharedRef< SWidget > FGeoChatTestModule::GenerateChatMenuContent()
{
	FMenuBuilder MenuBuilder(true, nullptr);
	MenuBuilder.BeginSection("hook", LOCTEXT("Chat_Labels", "Chat room"));
	
	//~ Hardcoded chats, we can add more
	FUIAction Chat1Action(FExecuteAction::CreateLambda([this](){
		ChatRoom->OpenChatWindow("Chat 01");
	}));
	
	FUIAction Chat2Action(FExecuteAction::CreateLambda([this]() {
		ChatRoom->OpenChatWindow("Chat 02");
		}));

	MenuBuilder.AddMenuEntry(LOCTEXT("Chat_Labels01", "Chat 01"), LOCTEXT("Chat_Labels", "Chats"), FSlateIcon(), Chat1Action);
	MenuBuilder.AddMenuEntry(LOCTEXT("Chat_Labels02", "Chat 02"), LOCTEXT("Chat_Labels", "Chats2"), FSlateIcon(), Chat2Action);

	MenuBuilder.EndSection();

	return MenuBuilder.MakeWidget();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGeoChatTestModule, GeoChatTest)