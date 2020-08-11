// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GeoChatTestStyle.h"

class FGeoChatTestCommands : public TCommands<FGeoChatTestCommands>
{
public:

	FGeoChatTestCommands()
		: TCommands<FGeoChatTestCommands>(TEXT("GeoChatTest"), NSLOCTEXT("Contexts", "GeoChatTest", "GeoChatTest Plugin"), NAME_None, FGeoChatTestStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
