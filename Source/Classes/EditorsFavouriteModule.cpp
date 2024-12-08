// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AssetViewUtils.h"

#include "ContentBrowserModule.h"
#include "ContentBrowserDataSubsystem.h"
#include "IContentBrowserDataModule.h"

#include "Interfaces/IPluginManager.h"

#include "Settings/EditorsFavouriteSettings.h"

#define LOCTEXT_NAMESPACE "EditorsFavourite"

class FEditorsFavouriteModule final : public IModuleInterface
{
public:
    //~ Begin IModuleInterface
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    //~ End IModuleInterface

private:
    /** Called right after the engine is initialized. */
    void OnEngineInit();
    
    /** Called right before the engine is exiting. */
    void OnEnginePreExit();

    void OnRequestUpdate(UEditorsFavouriteSettings* SettingsObject);
    void OnItemDataUpdated(TArrayView<const FContentBrowserItemDataUpdate> DataUpdates);
};
IMPLEMENT_MODULE(FEditorsFavouriteModule, EditorsFavourite)
typedef TMap<FString, TArray<FString>> FFolderDirMap;

//********************************************************************************************************************
//
// FEditorsFavouriteModule implementation
//
//********************************************************************************************************************

namespace UE::EditorsFavourite
{
    void NormalizeDirectoryPaths(TArray<FString>& InOutPaths)
    {
        FString ProjectDir = FPaths::ProjectDir();
        FPaths::NormalizeDirectoryName(ProjectDir);
        
        for (FString& Path : InOutPaths)
        {
            FPaths::NormalizeDirectoryName(Path);

            // Remove the project directory from the path
            // Example: "C:/Users/Username/Documents/Unreal Projects/ProjectName/Content/SomeFolder" -> "Content/SomeFolder"
            if (Path.StartsWith(ProjectDir))
            {
                Path = Path.RightChop(ProjectDir.Len());
            }

            if (Path.StartsWith(TEXT("/Content/")))
            {
                Path.ReplaceInline(TEXT("/Content/"), TEXT("/Game/"));   
            }
        }
    }

    void NormalizePluginDirectoryPaths(FFolderDirMap& InOutDirMap)
    {
        for (auto& KVP : InOutDirMap)
        {
            const FString PluginName = KVP.Key;

            for (FString& Path : KVP.Value)
            {
                FPaths::NormalizeDirectoryName(Path);

                // Remove the plugin directory from the path
                // Find the plugin name in the path and remove everything before it including the plugin name
                int32 PluginNameIndex = Path.Find(PluginName);
                if (PluginNameIndex != INDEX_NONE)
                {
                    Path = Path.RightChop(PluginNameIndex + PluginName.Len());
                }

                // Replace the "Content" directory with the plugin name
                if (Path.StartsWith(TEXT("/Content/")))
                {
                    // Convert "PluginName" to "/PluginName/"
                    const FString NewPath = FString::Printf(TEXT("/%s/"), *PluginName);
                    Path.ReplaceInline(TEXT("/Content/"), *NewPath);
                }
            }
        }
    }

    void FilterOutBlacklistedFolders(const TArray<FString>& InFolders, TArray<FString>& OutFolders, TArray<FString>& OutBlacklisted, const UEditorsFavouriteSettings* Settings)
    {
        for (const FString& Folder : InFolders)
        {
            if (!Settings->IsFolderInBlacklist(Folder))
            {
                OutFolders.Add(Folder);
            }
            else
            {
                OutBlacklisted.Add(Folder);
            }
        }
    }

    void ColorizeFolders(const TArray<FString>& InFolders, const TArray<FString>& InBlacklistedFolders, const UEditorsFavouriteSettings* Settings)
    {
        
        // Colorize the folders
        for (const FString& Folder : InFolders)
        {
            FLinearColor FolderColor;
            if (Settings->GetFolderColor(Folder, FolderColor))
            {
                AssetViewUtils::SetPathColor(Folder, FolderColor);
            }
        }

        // Clear the color of the blacklisted folders
        if (Settings->ShouldClearBlacklistedFolderColors())
        {
            for (const FString& Folder : InBlacklistedFolders)
            {
                AssetViewUtils::SetPathColor(Folder, TOptional<FLinearColor>());
            }
        }
    }
}

void FEditorsFavouriteModule::StartupModule()
{
    FCoreDelegates::OnEnginePreExit.AddRaw(this, &FEditorsFavouriteModule::OnEnginePreExit);
    FCoreDelegates::OnPostEngineInit.AddRaw(this, &FEditorsFavouriteModule::OnEngineInit);
}

void FEditorsFavouriteModule::ShutdownModule()
{
    FCoreDelegates::OnEnginePreExit.RemoveAll(this);
    FCoreDelegates::OnPostEngineInit.RemoveAll(this);
}

void FEditorsFavouriteModule::OnEngineInit()
{
    if (UEditorsFavouriteSettings* Settings = UEditorsFavouriteSettings::Get())
    {
        Settings->OnRequestLiveUpdate().AddRaw(this, &FEditorsFavouriteModule::OnRequestUpdate);
        OnRequestUpdate(Settings); // Call the update function once to colorize the folders
    }

    // Assign a delegate that triggers whenever a folder is added to the content browser
    if (const IContentBrowserDataModule* ContentBrowserDataModule = IContentBrowserDataModule::GetPtr())
    {
        ContentBrowserDataModule->GetSubsystem()->OnItemDataUpdated().AddRaw(this, &FEditorsFavouriteModule::OnItemDataUpdated);
    }
}

void FEditorsFavouriteModule::OnEnginePreExit()
{
    if (UEditorsFavouriteSettings::Get())
    {
        UEditorsFavouriteSettings::SaveEditorsFavouriteConfig();
    }
}

void FEditorsFavouriteModule::OnRequestUpdate(UEditorsFavouriteSettings* SettingsObject)
{
    if (SettingsObject == nullptr)
    {
        return;
    }
    
    IFileManager& FileManager = IFileManager::Get();
    
    auto GetSubFolders = [&FileManager](const FString& FolderPath, TArray<FString>& OutFolders)
    {
        TArray<FString> LocalFolders;
        FileManager.FindFilesRecursive(LocalFolders, *FolderPath, TEXT("*"), false, true, false);
        if (UEditorsFavouriteSettings* Settings = UEditorsFavouriteSettings::Get())
        {
            for (const FString& Folder : LocalFolders)
            {
                if (!Settings->IsFolderInBlacklist(Folder))
                {
                    OutFolders.Add(Folder);
                }
            }
        }
    };

    auto GetPluginFolders = [GetSubFolders](FFolderDirMap& OutFolders)
    {
        OutFolders.Reset();
        
        for (TSharedRef Plugin : IPluginManager::Get().GetDiscoveredPlugins())
        {
            if (Plugin->GetLoadedFrom() == EPluginLoadedFrom::Project)
            {
                TArray<FString> Dirs;
                GetSubFolders(Plugin->GetContentDir(), Dirs);
                OutFolders.Add(Plugin->GetName(), Dirs);
            }
        }
    };

    { // Specific folders
        const TArray<FEdFav_FolderColorMap>& FolderColorMaps = SettingsObject->GetFolderColorMaps();
        for (const auto& ColorMap : FolderColorMaps)
        {
            for (const auto& Specific : ColorMap.FolderPaths)
            {
                if (Specific.Path.IsEmpty()) continue;
                AssetViewUtils::SetPathColor(Specific.Path, ColorMap.FolderColor);
            }
        }
    }

    { // Project folders
        TArray<FString> Unfiltered, Filtered, Blacklisted;
        GetSubFolders(FPaths::ProjectContentDir(), Unfiltered);
        UE::EditorsFavourite::NormalizeDirectoryPaths(Unfiltered);
        UE::EditorsFavourite::FilterOutBlacklistedFolders(Unfiltered, Filtered, Blacklisted, SettingsObject);
        UE::EditorsFavourite::ColorizeFolders(Filtered, Blacklisted, SettingsObject);
    }

    // Plugin Folders
    if (SettingsObject->ShouldColorizePluginFolders())
    {
        FFolderDirMap PluginDirMap;
        GetPluginFolders(PluginDirMap);
        UE::EditorsFavourite::NormalizePluginDirectoryPaths(PluginDirMap);

        // Do some debug logging
        for (const auto& KVP : PluginDirMap)
        {
            TArray<FString> Filtered, Blacklisted;
            UE::EditorsFavourite::FilterOutBlacklistedFolders(KVP.Value, Filtered, Blacklisted, SettingsObject);
            UE::EditorsFavourite::ColorizeFolders(Filtered, Blacklisted, SettingsObject);
        }
    }
}

void FEditorsFavouriteModule::OnItemDataUpdated(TArrayView<const FContentBrowserItemDataUpdate> DataUpdates)
{
    UEditorsFavouriteSettings* Settings = UEditorsFavouriteSettings::Get();
    if (Settings == nullptr)
    {
        return;
    }

    if (!Settings->IsLiveUpdateEnabled())
    {
        return;
    }
    
    bool bShouldUpdate = false;
    for (const auto& Update : DataUpdates)
    {
        if (Update.GetItemData().IsFolder())
        {
            bShouldUpdate = true;
            break;
        }
    }

    if (bShouldUpdate)
    {
        OnRequestUpdate(UEditorsFavouriteSettings::Get());
    }
}
#undef LOCTEXT_NAMESPACE
