// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"

class FEditorsFavouriteCommands : public TCommands<FEditorsFavouriteCommands>
{
public:
	FEditorsFavouriteCommands();
	
	//~ Begin TCommands
	virtual void RegisterCommands() override;
	//~ End TCommands

public:
	TSharedPtr<FUICommandInfo> RestartEditor;
	TSharedPtr<FUICommandInfo> ExitEditor;
};