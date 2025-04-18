// Copyright © 2025 MajorT. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorsFavouriteTypes.h"
#include "Engine/DeveloperSettings.h"
#include "Preferences/UnrealEdOptions.h"

#include "EditorsFavouriteSettings.generated.h"

/** Settings for the Editors Favourite plugin */
UCLASS(Config = EditorPerProjectUserSettings, DisplayName = "Editors Favourite")
class UEditorsFavouriteSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UEditorsFavouriteSettings();
	
	DECLARE_EVENT_OneParam(UEditorsFavouriteSettings, FOnRequestLiveUpdate, UEditorsFavouriteSettings* /*Settings*/);
	FOnRequestLiveUpdate OnRequestLiveUpdate;

	/** Singleton-like access to the settings object */
	FORCEINLINE static UEditorsFavouriteSettings* Get()
	{
		return GetMutableDefault<UEditorsFavouriteSettings>();
	}

	EDITORSFAVOURITE_API void Init();

protected:
	//~ Begin UDeveloperSettings Interface
	virtual void PostLoad() override;
	
	virtual FName GetContainerName() const override;
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif
	//~ End UDeveloperSettings Interface
#if WITH_EDITOR
	//~ Begin UObject Interface
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject Interface
#endif

public:
	/** Returns whether folders should update immediately. */
	EDITORSFAVOURITE_API bool ShouldLiveUpdateFolders() const
	{
		return bLiveUpdateFolders;
	}

public:
	// ---------------------------------------------------------------------
	// Content Browser
	// ---------------------------------------------------------------------

	/** The currently applied theme. */
	UPROPERTY(config)
	FGuid CurrentAppliedTheme;

	/**
	 * Determines whether folders should update immediately after being created/renamed/deleted or if the settings have changed.
	 * This is enabled by default as it provides a more responsive experience.
	 *
	 * But if you have a large project with many folders, you may want to disable this to avoid performance issues.
	 * Taking effect after restarting the editor.
	 */
	UPROPERTY(Config, EditDefaultsOnly, Category = ContentBrowser)
	bool bLiveUpdateFolders = true;

	/**
	 * Determines whether folders that didn't fit into any scheme of the current theme should be reset to their default color.
	 * Note that this setting doesn't let you change the color of individual folders without a scheme.
	 */
	UPROPERTY(Config, EditDefaultsOnly, Category = ContentBrowser)
	bool bClearNotListedFolderColors = true;

	/**
	 * List of folders to ignore.
	 * DOESN'T WORK YET
	 */
	//UPROPERTY(VisibleDefaultsOnly, Category = ContentBrowser, meta = (RelativeToGameContentDir, LongPackageName))
	TArray<FDirectoryPath> FolderBlacklist;

	/**
	 * White-list of folders to show.
	 * If any folders are in this list, only those folders will be colorized.
	 * * DOESN'T WORK YET
	 */
	//UPROPERTY(VisibleDefaultsOnly, Category = ContentBrowser, meta = (RelativeToGameContentDir, LongPackageName))
	TArray<FDirectoryPath> FolderWhitelist;
	
	/** List of all known folder color themes. */
	TArray<FEdFav_FolderColorTheme> FolderColorThemes;

	// ---------------------------------------------------------------------
	// Dedicated Restart/Shutdown Button
	// ---------------------------------------------------------------------

	/** Determines whether the editor should show a dedicated restart button in the main toolbar. */
	UPROPERTY(Config, EditDefaultsOnly, Category = "Restart/Shutdown")
	bool bShowDedicatedRestartButton = true;
};
