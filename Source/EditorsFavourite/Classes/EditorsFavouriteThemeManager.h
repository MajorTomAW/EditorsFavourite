// Copyright © 2025 Playton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorsFavouriteTypes.h"
#include "UObject/Object.h"
#include "EditorsFavouriteThemeManager.generated.h"

UCLASS(Config = EditorSettings, MinimalAPI)
class UEditorsFavouriteThemeManager : public UObject
{
	GENERATED_BODY()
	friend class UEditorsFavouriteSettings;

public:
	EDITORSFAVOURITE_API UEditorsFavouriteThemeManager();
	
	static UEditorsFavouriteThemeManager& Get()
	{
		return *GetMutableDefault<UEditorsFavouriteThemeManager>();
	}

	const FGuid& GetCurrentThemeID() const
	{
		return CurrentThemeId;
	}

	const FEdFav_FolderColorScheme& GetColorScheme(int32 Index)
	{
		return ActiveSchemes.Schemes[Index];
	}

	void SetCurrentThemeId_Direct(FGuid InThemeId)
	{
		CurrentThemeId = InThemeId;
	}

	/** Initializes default schemes */
	EDITORSFAVOURITE_API void InitDefaults();

	/** Sets a default scheme to be used as a fallback if no theme is loaded */
	void SetDefaultScheme(int32 Id, FEdFav_FolderColorScheme InScheme)
	{
#if ALLOW_THEMES
		DefaultFolderColorSchemes[Id] = InScheme;
#else
		ActiveSchemes.Schemes[Id] = InScheme;
#endif
	}
	
#if ALLOW_THEMES
	DECLARE_EVENT_OneParam(UEditorsFavouriteSettings, FOnFolderColorThemeChanged, FGuid /*ThemeId*/);
	FOnFolderColorThemeChanged& OnFolderColorThemeChanged() { return ThemeChangedEvent; }

	/** Sets a custom display name for a folder color scheme */
	void SetSchemeDisplayName(int32 Id, FText DisplayName)
	{
		ActiveSchemes.DisplayNames[Id] = DisplayName;
	}

	/** Gets a custom display name for a folder color scheme. This will be empty if no custom name was chosen */
	FText GetSchemeDisplayName(int32 Id) const
	{
		return ActiveSchemes.DisplayNames[Id];
	}

	/** Loads all known themes from engine, project, and user directories */
	EDITORSFAVOURITE_API void LoadThemes();

	/** Saves the current theme to a file */
	EDITORSFAVOURITE_API void SaveCurrentThemeAs(const FString& InFilename);

	/** Applies a theme as the active theme */
	EDITORSFAVOURITE_API void ApplyTheme(FGuid ThemeId);

	/** Applies the default theme as the active theme */
	EDITORSFAVOURITE_API void ApplyDefaultTheme();

	/** Returns true if the active theme is an engine-specific theme */
	EDITORSFAVOURITE_API bool IsEngineTheme() const;

	/** Returns true if the active theme is a project-specific theme */
	EDITORSFAVOURITE_API bool IsProjectTheme() const;

	/** Removes a theme from the list of known themes */
	EDITORSFAVOURITE_API void RemoveTheme(FGuid ThemeId);

	/** Duplicates the active theme */
	EDITORSFAVOURITE_API FGuid DuplicateActiveTheme();

	/** Sets the display name for the current theme */
	EDITORSFAVOURITE_API void SetCurrentThemeDisplayName(FText NewDisplayName);

	/** Gets the current theme */
	const FEdFav_FolderColorTheme& GetCurrentTheme() const
	{
		return *Themes.FindByKey(CurrentThemeId);
	}

	/** Gets all known themes */
	const TArray<FEdFav_FolderColorTheme>& GetThemes() const
	{
		return Themes;
	}

	/** Validates that there is an active loaded theme */
	EDITORSFAVOURITE_API void ValidateActiveTheme();

	/** Returns the engine theme directory. (Engine themes are project-agnostic) */
	EDITORSFAVOURITE_API FString GetEngineThemeDir() const;

	/** Returns the project theme directory. (Project themes can override engine themes) */
	EDITORSFAVOURITE_API FString GetProjectThemeDir() const;

	/** Returns the user theme directory. (Themes in this directory are per-user and override engine and project themes) */
	EDITORSFAVOURITE_API FString GetUserThemeDir() const;

	/** Returns the plugins theme directory. */
	EDITORSFAVOURITE_API FString GetPluginThemeDir() const;

	/** Returns true if the theme ID already exists in the theme dropdown */
	EDITORSFAVOURITE_API bool DoesThemeExist(const FGuid& ThemeId) const;

private:
	FEdFav_FolderColorTheme& GetMutableCurrentTheme()
	{
		return *Themes.FindByKey(CurrentThemeId);
	}
	EDITORSFAVOURITE_API void LoadThemesFromDirectory(const FString& Directory);
	EDITORSFAVOURITE_API bool ReadTheme(const FString& ThemeData, FEdFav_FolderColorTheme& OutTheme);
	EDITORSFAVOURITE_API void EnsureValidCurrentTheme();
	EDITORSFAVOURITE_API void LoadThemeFolderSchemes(FEdFav_FolderColorTheme& Theme);

protected:
	//~ Begin UObject Interface
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	//~ End UObject Interface
	
private:
	FEdFav_FolderColorTheme DefaultFolderColorTheme;
	TArray<FEdFav_FolderColorTheme> Themes;
	FEdFav_FolderColorScheme DefaultFolderColorSchemes[ED_FAV_MAX_COLOR_SCHEMES];
	
	/** Broadcasts whenever the folder color theme changes. */
	FOnFolderColorThemeChanged ThemeChangedEvent;
#endif

	UPROPERTY(EditAnywhere, Config, Category=ContentBrowser)
	FGuid CurrentThemeId;

	UPROPERTY(EditAnywhere, Transient, Category=ContentBrowser)
	FEdFav_FolderColorSchemeList ActiveSchemes;
};
