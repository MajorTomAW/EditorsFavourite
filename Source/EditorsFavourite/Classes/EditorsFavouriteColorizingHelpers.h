// Copyright © 2025 Playton. All Rights Reserved.

#pragma once
#include "EditorsFavouriteSettings.h"


namespace UE::EditorsFavourite::Helpers
{
	/** Returns whether the path is in the game dir or plugin dir */
	inline void IsUnderGameOrPluginDir(const FString& InPath, bool& OutIsGameDir, bool& OutIsPluginDir)
	{
		OutIsGameDir = FPaths::IsUnderDirectory(InPath, *FPaths::ProjectContentDir());
		OutIsPluginDir = FPaths::IsUnderDirectory(InPath, *FPaths::ProjectPluginsDir());
	}

	/** Checks if this is a valid plugin to iterate through */
	inline bool ShouldIterateThroughPlugin(const TSharedRef<IPlugin>& Plugin)
	{
		return FPaths::IsUnderDirectory(Plugin->GetContentDir(), FPaths::ProjectPluginsDir()) &&
			Plugin->CanContainContent();
	}

	/** Builds a pretty string for a folder path */
	inline FString BuildPrettyDirPath(const FString& InPath, const FString& InRootName)
	{
		// Check if this is a game or plugin content directory
		bool bInProjectContent, bInPluginContent;
		IsUnderGameOrPluginDir(InPath, bInProjectContent, bInPluginContent);

		// Make the path relative to the corresponding content directory
		const FString Name = FPaths::GetCleanFilename(InPath);
		FString PrettyPath = InPath;
		if (bInProjectContent)
		{
			FPaths::MakePathRelativeTo(PrettyPath, *FPaths::ProjectContentDir());

			// Special case for the project content directory
			PrettyPath = TEXT("/") + InRootName + TEXT("/") + PrettyPath;
		}
		else if (bInPluginContent)
		{
			FPaths::MakePathRelativeTo(PrettyPath, *FPaths::ProjectPluginsDir());
		}

		// Remove the virtual path if it exists
		const FString OldPath = PrettyPath;
		const int32 ContentIdx = PrettyPath.Find(TEXT("Content"));
		if (ContentIdx != INDEX_NONE)
		{
			PrettyPath = TEXT("/") + InRootName + TEXT("/") +  PrettyPath.RightChop(ContentIdx + 8);
		}
		
		return PrettyPath;
	}

	/** Colorizes the folders in the content browser with the corresponding theme */
	inline void ColorizeDirsAccordingToScheme(const TArray<FString>& InDirs, const FEdFav_FolderColorScheme& Scheme, TArray<FString>& InOutTracking)
	{
		// Colorize explicit paths
		for (const FString& ExplicitDir : Scheme.ResolveExplicitPaths())
		{
			AssetViewUtils::SetPathColor(ExplicitDir, Scheme.SchemeColor);	
		}

		auto IsIncludedByScheme = [Scheme](const FString& Dir)
		{
			for (const FString& FolderName : Scheme.ResolveFolderNames())
			{
				if (FPaths::GetPathLeaf(Dir) == FolderName)
				{
					return true;
				}
			}
				
			return false;
		};

		// Colorize individual folders
		for (const FString& Dir : InDirs)
		{
			if (IsIncludedByScheme(Dir))
			{
				AssetViewUtils::SetPathColor(Dir, Scheme.SchemeColor);
				InOutTracking.RemoveSingle(Dir);
			}
		}
	}
	
	/** Directory iterator for the Editors Favourite plugin */
	class FEdFav_DirIterator : public IPlatformFile::FDirectoryVisitor
	{
	public:
		FEdFav_DirIterator(TArray<FString>& InOutDirs)
			: OutDirs(InOutDirs)
		{
		}
		
		TArray<FString>& OutDirs;
		FString VirtualPath, RootName;

		void SetVirtualPath(const FString& InVirtualPath)
		{
			VirtualPath = InVirtualPath;
		}

		void SetRootName(const FString& InRootName)
		{
			RootName = InRootName;
		}

		virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
		{
			FString FileOrDirString(FilenameOrDirectory);
			if (bIsDirectory)
			{
				// No need to check auto-generated folders for wp
				if (FileOrDirString.Contains(TEXT("__ExternalActors__")) ||
					FileOrDirString.Contains(TEXT("__ExternalObjects__")))
				{
					return true;
				}

				// Check if the directory is blacklisted
				for (const auto& BlackListedDir : UEditorsFavouriteSettings::Get()->FolderBlacklist)
				{
					if (FPaths::IsUnderDirectory(FilenameOrDirectory, BlackListedDir.Path))
					{
						return true;
					}
				}

				// Pretty up the path
				const FString PrettifiedPath = BuildPrettyDirPath(FilenameOrDirectory, RootName);

				// Add the directory to the list
				OutDirs.Add(PrettifiedPath);
			}
			
			return true;
		}
	};
}
