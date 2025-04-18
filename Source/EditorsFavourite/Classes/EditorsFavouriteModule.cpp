// Copyright © 2025 MajorT. All Rights Reserved.


#include "IEditorsFavouriteModule.h"

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AssetViewUtils.h"
#include "ContentBrowserDataSubsystem.h"
#include "EditorsFavouriteColorizingHelpers.h"
#include "EditorsFavouriteEditorToolbar.h"
#include "EditorsFavouriteSettings.h"
#include "EditorsFavouriteThemeManager.h"
#include "IContentBrowserDataModule.h"
#include "Customization/EdFavFolderColorSchemeCustomization.h"
#include "Interfaces/IMainFrameModule.h"

#define LOCTEXT_NAMESPACE "EditorsFavourite"

using namespace UE::EditorsFavourite::Helpers;

/** Module implementation */
class FEditorsFavouriteModule final : public IEditorsFavouriteModule
{
public:
	//~ Begin IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ End IModuleInterface

	//~ Begin IEditorsFavouriteModule
	virtual TSharedPtr<FUICommandList> GetCommandList() const override { return CommandList; }
	//~ End IEditorsFavouriteModule

private:
	void OnPostEngineInit();
	
	void StartColorizingFolders();
	void RequestFolderColorUpdate();

	void OnItemDataUpdated(TArrayView<const FContentBrowserItemDataUpdate> DataUpdates);
	void OnRequestUpdate(FGuid);

	void RestartApplication() const;
	void ExitApplication() const;
private:
	/** Commands to use for exit/restarting the editor */
	TSharedPtr<FUICommandList> CommandList;
};
IMPLEMENT_MODULE(FEditorsFavouriteModule, EditorsFavourite)

//********************************************************************************************************************
//
// FEditorsFavouriteModule implementation
//
//********************************************************************************************************************

void FEditorsFavouriteModule::StartupModule()
{
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FEditorsFavouriteModule::OnPostEngineInit);
}

void FEditorsFavouriteModule::ShutdownModule()
{
	FCoreDelegates::OnPostEngineInit.RemoveAll(this);
	FEditorsFavouriteCommands::Unregister();

	if (const IContentBrowserDataModule* ContentBrowser = IContentBrowserDataModule::GetPtr())
	{
		if (UContentBrowserDataSubsystem* ContentBrowserSub = ContentBrowser->GetSubsystem())
		{
			ContentBrowserSub->OnItemDataUpdated().RemoveAll(this);
		}
	}
}

void FEditorsFavouriteModule::OnPostEngineInit()
{
	StartColorizingFolders();
	
#if ALLOW_THEMES
	UEditorsFavouriteThemeManager::Get().LoadThemes();
#endif

	UEditorsFavouriteSettings* Settings = UEditorsFavouriteSettings::Get();
	Settings->Init();
	
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.RegisterCustomPropertyTypeLayout("EdFav_FolderColorSchemeList",
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FEdFavFolderColorSchemeCustomization::MakeInstance));
	PropertyEditorModule.RegisterCustomClassLayout("EditorsFavouriteSettings",
		FOnGetDetailCustomizationInstance::CreateStatic(&FEdFavSettingsCustomization::MakeInstance));

	PropertyEditorModule.NotifyCustomizationModuleChanged();

	// Request initial update
	RequestFolderColorUpdate();


	// Commands & Toolbar
	FEditorsFavouriteCommands::Register();
	CommandList = MakeShareable(new FUICommandList);
	CommandList->MapAction
	(
		FEditorsFavouriteCommands::Get().RestartEditor,
		FExecuteAction::CreateRaw(this, &FEditorsFavouriteModule::RestartApplication),
		FCanExecuteAction()
	);
	CommandList->MapAction
	(
		FEditorsFavouriteCommands::Get().ExitEditor,
		FExecuteAction::CreateRaw(this, &FEditorsFavouriteModule::ExitApplication),
		FCanExecuteAction()
	);

	// Let the main frame module know about our commands
	IMainFrameModule& MainFrame = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	MainFrame.GetMainFrameCommandBindings()->Append(CommandList.ToSharedRef());

	FEditorsFavouriteLevelEditorToolbar::RegisterToolBar(CommandList);
}

void FEditorsFavouriteModule::RestartApplication() const
{
	FUnrealEdMisc::Get().RestartEditor(false);
}

void FEditorsFavouriteModule::ExitApplication() const
{
	FSlateApplication::Get().LeaveDebuggingMode();
	GEngine->DeferredCommands.Add(TEXT("CLOSE_SLATE_MAINFRAME"));
}

void FEditorsFavouriteModule::StartColorizingFolders()
{
	UEditorsFavouriteThemeManager::Get().OnFolderColorThemeChanged().AddRaw(this, &FEditorsFavouriteModule::OnRequestUpdate);

	// Assign a delegate that triggers whenever a new item is added to the content browser
	// I honestly dont know if this is the right way to do it, but it works
	// Also I didn't experience any performance issues yet, so i guess it's fine :p
	if (const IContentBrowserDataModule* ContentBrowser = IContentBrowserDataModule::GetPtr())
	{
		ContentBrowser->GetSubsystem()->OnItemDataUpdated().AddRaw(this, &FEditorsFavouriteModule::OnItemDataUpdated);
	}
}

void FEditorsFavouriteModule::RequestFolderColorUpdate()
{
	IFileManager& FileManager = IFileManager::Get();
	IPluginManager& PluginManager = IPluginManager::Get();
	UEditorsFavouriteThemeManager& ThemeManager = UEditorsFavouriteThemeManager::Get();

	TArray<FString> Dirs;
	FEdFav_DirIterator DirIterator(Dirs);

	// Scan the game content directory
	DirIterator.SetRootName(TEXT("Game"));
	FileManager.IterateDirectoryRecursively(*FPaths::ProjectContentDir(), DirIterator);

	// Scan the plugin content directories
	TArray<TSharedRef<IPlugin>> DiscoveredPlugins = PluginManager.GetDiscoveredPlugins();
	for (TSharedRef Plugin : DiscoveredPlugins)
	{
		if (ShouldIterateThroughPlugin(Plugin))
		{
			// Update virtual-path so we can remove it
			DirIterator.SetVirtualPath(Plugin->GetDescriptor().EditorCustomVirtualPath);
			DirIterator.SetRootName(Plugin->GetName());
			
			FileManager.IterateDirectoryRecursively(*Plugin->GetContentDir(), DirIterator);
		}
	}

	// Colorize the folders
	TArray<FString> Tracking = Dirs;
	for (int i = 0; i < ED_FAV_MAX_COLOR_SCHEMES; ++i)
	{
		ColorizeDirsAccordingToScheme(Dirs, ThemeManager.GetColorScheme(i), Tracking);
	}

	// Clear the tracking array
	if (UEditorsFavouriteSettings::Get()->bClearNotListedFolderColors)
	{
		for (const FString& Dir : Tracking)
		{
			AssetViewUtils::SetPathColor(Dir, TOptional<FLinearColor>());
		}	
	}
}

void FEditorsFavouriteModule::OnItemDataUpdated(TArrayView<const FContentBrowserItemDataUpdate> DataUpdates)
{
	// Maybe we shouldn't even bind to this event if we don't want to live update folders
	// But that would mean we would have to restart the editor to apply the settings
	if (!UEditorsFavouriteSettings::Get()->ShouldLiveUpdateFolders())
	{
		return;
	}

	// Request a folder update if any of the items are folders
	for (const auto& Data : DataUpdates)
	{
		if (Data.GetItemData().IsFolder())
		{
			RequestFolderColorUpdate();
			return;
		}
	}
}

void FEditorsFavouriteModule::OnRequestUpdate(FGuid)
{
	// Maybe we shouldn't even bind to this event if we don't want to live update folders
	// But that would mean we would have to restart the editor to apply the settings
	if (!UEditorsFavouriteSettings::Get()->ShouldLiveUpdateFolders())
	{
		return;
	}
	
	RequestFolderColorUpdate();
}

#undef LOCTEXT_NAMESPACE
