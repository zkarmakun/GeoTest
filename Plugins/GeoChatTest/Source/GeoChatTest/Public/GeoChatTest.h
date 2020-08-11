// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FGeoChatTestModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	
private:
	/* Register new menus*/
	void RegisterMenus();

	/*Generate chat list menu*/
	TSharedRef< SWidget > GenerateChatMenuContent();

private:
	/* Commands*/
	TSharedPtr<class FUICommandList> PluginCommands;

	/* Unique instance of chat room*/
	TSharedPtr<class FChatRoom> ChatRoom;
};
