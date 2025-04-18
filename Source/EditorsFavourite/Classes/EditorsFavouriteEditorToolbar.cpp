// Copyright © 2025 Playton. All Rights Reserved.


#include "EditorsFavouriteEditorToolbar.h"

#include "EditorsFavouriteSettings.h"
#include "IEditorsFavouriteModule.h"
//#include "Commands/EditorsFavouriteCommands.h"

#define LOCTEXT_NAMESPACE "EditorsFavourite"

void FEditorsFavouriteLevelEditorToolbar::RegisterToolBar(const TSharedPtr<FUICommandList>& CommandList)
{
	FToolMenuOwnerScoped OwnerScoped(UE_MODULE_NAME);
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.ModesToolBar");

	FToolMenuSection& Section = Menu->FindOrAddSection("File", TAttribute<FText>());
	FToolMenuEntry Entry = FToolMenuEntry::InitComboButton
	(
		"ApplicationActions",
		FUIAction
		(
			FExecuteAction(),
			FCanExecuteAction(),
			FIsActionChecked(),
			FIsActionButtonVisible::CreateLambda([]()
			{
				return UEditorsFavouriteSettings::Get()->bShowDedicatedRestartButton;
			})
		),
		FOnGetContent::CreateStatic(&GetApplicationActions),
		TAttribute<FText>(),
		LOCTEXT("ApplicationActions_ToolTip", "Application Actions"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "MainFrame.Exit"),
		false,
		NAME_None
	);
	Entry.SetCommandList(CommandList);
	Entry.InsertPosition = FToolMenuInsert("SaveAllLevels", EToolMenuInsertType::First);
	
	Section.AddEntry(Entry);
}

TSharedRef<SWidget> FEditorsFavouriteLevelEditorToolbar::GetApplicationActions()
{
	TSharedPtr<const FUICommandList> CommandList = IEditorsFavouriteModule::Get().GetCommandList();
	
	FMenuBuilder MenuBuilder(true, CommandList);
	
	MenuBuilder.AddMenuEntry(
		FEditorsFavouriteCommands::Get().ExitEditor,
		NAME_None,
		TAttribute<FText>(),
		TAttribute<FText>(),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "MainFrame.Exit")
		);
	
	MenuBuilder.AddMenuEntry(
		FEditorsFavouriteCommands::Get().RestartEditor,
		NAME_None,
		TAttribute<FText>(),
		TAttribute<FText>(),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "GenericCommands.Undo")
		);
	
	return MenuBuilder.MakeWidget(nullptr, 200.f);
}



FEditorsFavouriteCommands::FEditorsFavouriteCommands()
	: TCommands
	(TEXT("EditorsFavourite"),
		LOCTEXT("EditorsFavouriteCommands", "Editor's Favourite Plugin"),
		NAME_None,
		FAppStyle::GetAppStyleSetName())
{
}

void FEditorsFavouriteCommands::RegisterCommands()
{
	UI_COMMAND
	(
		RestartEditor,
		"Restart",
		"Restarts the Application.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::R)
	);

	UI_COMMAND
	(
		ExitEditor,
		"Exit",
		"Exits the Application.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::E)
	);
}
