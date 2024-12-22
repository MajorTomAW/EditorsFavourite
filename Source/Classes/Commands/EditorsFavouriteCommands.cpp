// Copyright Epic Games, Inc. All Rights Reserved.


#include "EditorsFavouriteCommands.h"

#define LOCTEXT_NAMESPACE "EditorsFavourite"

FEditorsFavouriteCommands::FEditorsFavouriteCommands()
	: TCommands
	(
		TEXT("EditorsFavourite"),
		LOCTEXT("EditorsFavouriteCommands", "Editors Favourite Plugin"),
		NAME_None,
		FAppStyle::GetAppStyleSetName()
	)
{
}

void FEditorsFavouriteCommands::RegisterCommands()
{
	UI_COMMAND(
		RestartEditor,
		"Restart",
		"Restarts the Application",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::R));

	UI_COMMAND(
		ExitEditor,
		"Exit",
		"Exits the Application",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::E)
		);
}

#undef LOCTEXT_NAMESPACE
