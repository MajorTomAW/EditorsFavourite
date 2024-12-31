// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Preferences/UnrealEdOptions.h"
#include "EditorsFavouriteSettings.generated.h"

// Custom metadata for properties in the EditorsFavouriteSettings class.
namespace UM
{
	enum
	{
		// [PropertyMetadata] Indicates that this property should get saved to the config file immediately after it has been changed.
		SaveImmediately,

		// [PropertyMetadata] Indicates that this property should update the editor immediately after it has been changed.
		LiveUpdate,
	};
}

/**
 * FEdFav_FolderColorMap
 *
 * Wrapper struct for customizing the folder color map.
 */
USTRUCT()
struct FEdFav_FolderColorMap
{
	GENERATED_BODY()
	friend class UEditorsFavouriteSettings;

	FEdFav_FolderColorMap()
		: FolderColor(FLinearColor::White)
	{
	}
	
public:
	/** A list of folder names that will be colored */
	UPROPERTY(EditDefaultsOnly, Category = "ColorMap", meta = (LiveUpdate))
	TSet<FString> FolderNames;

	/** A list of specific paths that will be colored */
	UPROPERTY(EditDefaultsOnly, Category = "ColorMap", AdvancedDisplay, meta = (RelativeToGameContentDir, LongPackageName, LiveUpdate))
	TArray<FDirectoryPath> FolderPaths;

	/** The color to apply to the appropriate folder names */
	UPROPERTY(EditDefaultsOnly, Category = "ColorMap", meta = (LiveUpdate))
	FLinearColor FolderColor;
};

/**
 * FEdFav_FolderColorTheme
 *
 * Wrapper struct for customizing the EditorsFavourite settings.
 */
USTRUCT()
struct FEdFav_FolderColorTheme
{
	GENERATED_BODY()
	friend class UEditorsFavouriteSettings;

	FEdFav_FolderColorTheme();
	explicit FEdFav_FolderColorTheme(const bool bInIsCustomProfile, const FString& InProfileName)
		: ProfileName(InProfileName)
		, bIsCustomProfile(bInIsCustomProfile)
	{
	}

public:
	/** The name of the profile */
	UPROPERTY(EditAnywhere, Category = "Profile", meta = (EditCondition = "bIsCustomProfile"))
	FString ProfileName;

	/** List of folders to ignore */
	UPROPERTY(EditDefaultsOnly, Category = "Profile", AdvancedDisplay, meta = (RelativeToGameContentDir, LongPackageName, LiveUpdate))
	TArray<FDirectoryPath> FolderBlacklist;

	/** The folder color map */
	UPROPERTY(EditDefaultsOnly, Category = "Profile", meta = (LiveUpdate))
	TArray<FEdFav_FolderColorMap> FolderColorMaps;
	
private:
	/** This allows the profile to be renamed or deleted */
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = false, EditConditionHides))
	uint32 bIsCustomProfile : 1;
};

/**
 * UEditorsFavouriteSettings
 *
 * Settings class for the EditorsFavourite module.
 */
UCLASS(Config = Editor)
class UEditorsFavouriteSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnRequestLiveUpdate, UEditorsFavouriteSettings* /*SettingsObject*/);
	FORCEINLINE FOnRequestLiveUpdate& OnRequestLiveUpdate() { return RequestLiveUpdateDelegate; }
	UEditorsFavouriteSettings();

	/** Singleton-like access to the settings object */
	FORCEINLINE static UEditorsFavouriteSettings* Get()
	{
		return GetMutableDefault<UEditorsFavouriteSettings>();
	}

	/** Save the settings to the config file */
	static void SaveEditorsFavouriteConfig(bool bSaveGlobal = false);

public:
	bool GetFolderColor(const FString& FolderPath, FLinearColor& OutColor) const;
	bool IsFolderInBlacklist(const FString& FolderPath) const;
	bool IsLiveUpdateEnabled() const { return bLiveUpdateFolderColors; }
	bool ShouldClearBlacklistedFolderColors() const { return bClearBlacklistedFolderColors; }
	bool ShouldColorizePluginFolders() const { return bColorizePluginFolders; }
	const TArray<FEdFav_FolderColorMap>& GetFolderColorMaps() const { return FolderColorTheme.FolderColorMaps; }

protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	//~ Begin UDeveloperSettings Interface
	virtual FName GetCategoryName() const override;
	virtual FName GetContainerName() const override;
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif
	//~ End UDeveloperSettings Interface

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	virtual void PostInitProperties() override;
	//~ End UObject Interface

protected: // CONTENT BROWSER
	/** Whether to live update the folder colors */
	UPROPERTY(Config, EditDefaultsOnly, Category = "Content Browser")
	bool bLiveUpdateFolderColors;

	/** Whether to clear the color of the blacklisted folders */
	UPROPERTY(Config, EditDefaultsOnly, Category = "Content Browser")
	bool bClearBlacklistedFolderColors;

	/** Whether to also colorize the folders that are inside plugins */
	UPROPERTY(Config, EditDefaultsOnly, Category = "Content Browser")
	bool bColorizePluginFolders;
	
	/** The default profile */
	UPROPERTY(Config, EditDefaultsOnly, Category = "Content Browser", meta = (LiveUpdate))
	FEdFav_FolderColorTheme FolderColorTheme;

	/** Holds a delegate executed after the settings section has been modified, and the editor should be updated. */
	FOnRequestLiveUpdate RequestLiveUpdateDelegate;


protected: // BLUEPRINT COMMON CLASSES
	/** Override the default blueprint class picker */
	UPROPERTY(EditDefaultsOnly, Category = "Blueprint Class Picker", meta = (SaveImmediately))
	bool bOverrideBlueprintClassPicker;
	
	/** List of classes that are common in the blueprint class dialog */
	UPROPERTY(EditDefaultsOnly, Category = "Blueprint Class Picker", meta = (SaveImmediately, ShowTreeView = true, AllowAbstract))
	TSet<FSoftClassPath> CommonClasses;
};
