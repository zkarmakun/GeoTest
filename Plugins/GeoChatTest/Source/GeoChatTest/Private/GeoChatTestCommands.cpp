// Copyright Epic Games, Inc. All Rights Reserved.

#include "GeoChatTestCommands.h"

#define LOCTEXT_NAMESPACE "FGeoChatTestModule"

void FGeoChatTestCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "GeoChatTest", "Execute GeoChatTest action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
