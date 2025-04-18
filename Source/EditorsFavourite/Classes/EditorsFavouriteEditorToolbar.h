// Copyright © 2025 Playton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FUICommandList;
class SWidget;

class FEditorsFavouriteLevelEditorToolbar
{
public:
	static void RegisterToolBar(const TSharedPtr<FUICommandList>& CommandList);

private:
	static TSharedRef<SWidget> GetApplicationActions();
};

class FEditorsFavouriteCommands : public TCommands<FEditorsFavouriteCommands>
{
public:
	FEditorsFavouriteCommands();

	//~ Begin TCommands interface
	virtual void RegisterCommands() override;
	//~ End TCommands interface

public:
	TSharedPtr<FUICommandInfo> RestartEditor;
	TSharedPtr<FUICommandInfo> ExitEditor;
};