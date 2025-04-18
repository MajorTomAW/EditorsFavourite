// Copyright © 2025 Playton. All Rights Reserved.


#include "EditorsFavouriteThemeManager.h"

#include "Interfaces/IPluginManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EditorsFavouriteThemeManager)

#define LOCTEXT_NAMESPACE "EditorsFavourite"

static const FString ThemesSubDir = TEXT("Slate/Themes/ContentBrowser");

UEditorsFavouriteThemeManager::UEditorsFavouriteThemeManager()
{
	InitDefaults();
}

void UEditorsFavouriteThemeManager::InitDefaults()
{
	// Fill in the default (empty) schemes
	for (int i = 0; i < ED_FAV_MAX_COLOR_SCHEMES; ++i)
	{
		DefaultFolderColorSchemes[i] = FEdFav_FolderColorScheme();
	}
}

void UEditorsFavouriteThemeManager::LoadThemes()
{
	Themes.Empty();

	// Load themes from engine, project, and user directories
	LoadThemesFromDirectory(GetPluginThemeDir());
	LoadThemesFromDirectory(GetEngineThemeDir());
	LoadThemesFromDirectory(GetProjectThemeDir());
	LoadThemesFromDirectory(GetUserThemeDir());

	EnsureValidCurrentTheme();
	ApplyTheme(CurrentThemeId);
}

void UEditorsFavouriteThemeManager::SaveCurrentThemeAs(const FString& FileName)
{
	FEdFav_FolderColorTheme& CurrentTheme = GetMutableCurrentTheme();
	CurrentTheme.Filename = FileName;
	FString NewPath = CurrentTheme.Filename;
	{ // Save json
		FString Output;
		TSharedRef<TJsonWriter<>> WriterRef = TJsonWriterFactory<>::Create(&Output);
		TJsonWriter<>& Writer = WriterRef.Get();
		Writer.WriteObjectStart();
		Writer.WriteValue(TEXT("Version"), 1);
		Writer.WriteValue(TEXT("Id"), CurrentTheme.Id.ToString());
		Writer.WriteValue(TEXT("DisplayName"), CurrentTheme.DisplayName.ToString());
		
		{
			Writer.WriteObjectStart(TEXT("Schemes"));
			for (int32 SchemeIndex = 0; SchemeIndex < ED_FAV_MAX_COLOR_SCHEMES; ++SchemeIndex)
			{
				const FEdFav_FolderColorScheme& Scheme = ActiveSchemes.Schemes[SchemeIndex];
				Writer.WriteObjectStart(FString::FromInt(SchemeIndex));

				{ // Scheme Color
					Writer.WriteValue(TEXT("SchemeColor"), Scheme.SchemeColor.ToString());
				}
				{ // Folder Names
					Writer.WriteArrayStart(TEXT("FolderNames"));
					for (const FString& FolderName : Scheme.ResolveFolderNames())
					{
						Writer.WriteValue(FolderName);
					}
					Writer.WriteArrayEnd();
				}
				{ // Explicit Paths
					Writer.WriteArrayStart(TEXT("ExplicitPaths"));
					for (const FString& ExplicitPath : Scheme.ResolveExplicitPaths())
					{
						Writer.WriteValue(ExplicitPath);
					}
					Writer.WriteArrayEnd();
				}

				Writer.WriteObjectEnd();
			}
			Writer.WriteObjectEnd();
		}

		Writer.WriteObjectEnd();
		Writer.Close();

		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FileName))
		{
			FPlatformFileManager::Get().GetPlatformFile().SetReadOnly(*FileName, false);

			// Create a new path if the filename has been changed.
			NewPath = GetUserThemeDir() / CurrentTheme.DisplayName.ToString() + TEXT(".json");

			if (!NewPath.Equals(CurrentTheme.Filename))
			{
				IFileManager::Get().Move(*NewPath, *FileName);
			}
		}

		FFileHelper::SaveStringToFile(Output, *NewPath);
	}
}

void UEditorsFavouriteThemeManager::ApplyTheme(FGuid ThemeId)
{
	if (ThemeId.IsValid())
	{
		FEdFav_FolderColorTheme* CurrentTheme = nullptr;
		if (CurrentThemeId != ThemeId)
		{
			// Unload the current theme
			if (CurrentThemeId.IsValid())
			{
				CurrentTheme = &GetMutableCurrentTheme();
				// Unload existing schemes
				CurrentTheme->LoadedDefaultColorSchemes.Empty();
			}

			// Load the new theme
			FEdFav_FolderColorTheme* Theme = Themes.FindByKey(ThemeId);
			if (Theme)
			{
				CurrentThemeId = ThemeId;
				SaveConfig();
			}
		}

		CurrentTheme = &GetMutableCurrentTheme();
		LoadThemeFolderSchemes(*CurrentTheme);

		// Apply the new colors
		if (CurrentTheme->LoadedDefaultColorSchemes.Num() > 0)
		{
			FMemory::Memcpy(ActiveSchemes.Schemes, CurrentTheme->LoadedDefaultColorSchemes.GetData(), sizeof(FEdFav_FolderColorScheme) * CurrentTheme->LoadedDefaultColorSchemes.Num());
		}
	}
	OnFolderColorThemeChanged().Broadcast(CurrentThemeId);
}

void UEditorsFavouriteThemeManager::ApplyDefaultTheme()
{
	ApplyTheme(DefaultFolderColorTheme.Id);
}

bool UEditorsFavouriteThemeManager::IsEngineTheme() const
{
	// users cannot edit/delete engine-specific themes: 
	const FString EnginePath = GetEngineThemeDir() / GetCurrentTheme().DisplayName.ToString() + TEXT(".json");

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	if (GetCurrentTheme() == DefaultFolderColorTheme)
	{
		return true;
	}
	if (FileManager.FileExists(*EnginePath))
	{
		return true;
	}
	return false;
}

bool UEditorsFavouriteThemeManager::IsProjectTheme() const
{
	// users cannot edit/delete project-specific themes: 
	const FString ProjectPath = GetProjectThemeDir() / GetCurrentTheme().DisplayName.ToString() + TEXT(".json");

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile(); 

	if (FileManager.FileExists(*ProjectPath))
	{
		return true; 
	}
	return false; 
}

void UEditorsFavouriteThemeManager::RemoveTheme(FGuid ThemeId)
{
	// Current Theme cannot currently be removed.  Apply a new theme first
	if (CurrentThemeId != ThemeId)
	{
		Themes.RemoveAll([&ThemeId](const FEdFav_FolderColorTheme& TestTheme) { return TestTheme.Id == ThemeId; });
	}
}

FGuid UEditorsFavouriteThemeManager::DuplicateActiveTheme()
{
	const FEdFav_FolderColorTheme& CurrentTheme = GetCurrentTheme();

	FGuid NewThemeGuid = FGuid::NewGuid();
	FEdFav_FolderColorTheme NewTheme;
	NewTheme.Id = NewThemeGuid;
	NewTheme.DisplayName = FText::Format(LOCTEXT("ThemeDuplicateCopyText", "{0} - Copy"), CurrentTheme.DisplayName);
	NewTheme.LoadedDefaultColorSchemes = MakeArrayView<FEdFav_FolderColorScheme>(ActiveSchemes.Schemes, ED_FAV_MAX_COLOR_SCHEMES);

	Themes.Add(MoveTemp(NewTheme));

	return NewThemeGuid;
}

void UEditorsFavouriteThemeManager::SetCurrentThemeDisplayName(FText NewDisplayName)
{
	GetMutableCurrentTheme().DisplayName = NewDisplayName;
}

void UEditorsFavouriteThemeManager::ValidateActiveTheme()
{
	// This is necessary because the core style loads the color table before ProcessNewlyLoadedUObjects is called,
	// which means none of the config properties are in the class property link at that time.
	ReloadConfig();
	EnsureValidCurrentTheme();
	ApplyTheme(Get().GetCurrentTheme().Id);
}

FString UEditorsFavouriteThemeManager::GetEngineThemeDir() const
{
	return FPaths::EngineContentDir() / ThemesSubDir;
}

FString UEditorsFavouriteThemeManager::GetProjectThemeDir() const
{
	return FPaths::ProjectContentDir() / ThemesSubDir;
}

FString UEditorsFavouriteThemeManager::GetUserThemeDir() const
{
	return FPlatformProcess::UserSettingsDir() / FApp::GetEpicProductIdentifier() / ThemesSubDir;
}

FString UEditorsFavouriteThemeManager::GetPluginThemeDir() const
{
	IPluginManager& PluginManager = IPluginManager::Get();
	return PluginManager.FindPlugin("EditorsFavourite")->GetContentDir() / ThemesSubDir;
}

bool UEditorsFavouriteThemeManager::DoesThemeExist(const FGuid& ThemeId) const
{
	for (const auto& Theme : Themes)
	{
		if (Theme.Id == ThemeId)
		{
			return true;
		}
	}

	return false;
}

void UEditorsFavouriteThemeManager::LoadThemesFromDirectory(const FString& Directory)
{
	TArray<FString> ThemeFiles;
	IFileManager::Get().FindFiles(ThemeFiles, *Directory, TEXT(".json"));

	for (const FString& ThemeFile : ThemeFiles)
	{
		bool bValidFile = false;
		FString ThemeData;
		FString ThemeFilename = Directory / ThemeFile;
		if (FFileHelper::LoadFileToString(ThemeData, *ThemeFilename))
		{
			FEdFav_FolderColorTheme Theme;
			if (ReadTheme(ThemeData, Theme))
			{
				if (FEdFav_FolderColorTheme* ExistingTheme = Themes.FindByKey(Theme.Id))
				{
					// Just update the existing theme.
					// Themes with the same id can override an existing one.
					// This behavior mimics config file hierarchies
					ExistingTheme->Filename = MoveTemp(ThemeFilename);
				}
				else
				{
					// Theme not found, add a new one
					Theme.Filename = MoveTemp(ThemeFilename);
					Themes.Add(MoveTemp(Theme));
				}
			}
		}
	}
}

bool UEditorsFavouriteThemeManager::ReadTheme(const FString& ThemeData, FEdFav_FolderColorTheme& OutTheme)
{
	TSharedRef<TJsonReader<>> ReaderRef = TJsonReaderFactory<>::Create(ThemeData);
	TJsonReader<>& Reader = ReaderRef.Get();
	
	TSharedPtr<FJsonObject> ObjectPtr;
	if (FJsonSerializer::Deserialize(Reader, ObjectPtr) && ObjectPtr.IsValid())
	{
		int32 Version = 0;
		if (!ObjectPtr->TryGetNumberField(TEXT("Version"), Version))
		{
			return false;
		}

		FString IdString;
		if (!ObjectPtr->TryGetStringField(TEXT("Id"), IdString) || !FGuid::Parse(IdString, OutTheme.Id))
		{
			return false;
		}

		FString DisplayString;
		if (!ObjectPtr->TryGetStringField(TEXT("DisplayName"), DisplayString))
		{
			return false;
		}

		OutTheme.DisplayName = FText::FromString(MoveTemp(DisplayString));

		// Just check that the theme has schemes. We won't load them unless the theme is used
		if (!ObjectPtr->HasField(TEXT("Schemes")))
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	
	return true;
}

void UEditorsFavouriteThemeManager::EnsureValidCurrentTheme()
{
	DefaultFolderColorTheme.DisplayName = LOCTEXT("DefaultFolderColorTheme", "No Theme");
	DefaultFolderColorTheme.Id = FGuid(0x13438026, 0x5FBB4A9C, 0xA00A1DC9, 0x770217B8);
	DefaultFolderColorTheme.Filename = IPluginManager::Get().FindPlugin(TEXT("EditorsFavourite"))->GetBaseDir() / TEXT("Resources/Themes/NoTheme.json");

	int32 ThemeIndex = Themes.AddUnique(DefaultFolderColorTheme);

	if (!CurrentThemeId.IsValid() || !Themes.Contains(CurrentThemeId))
	{
		CurrentThemeId = DefaultFolderColorTheme.Id;
	}
}

void UEditorsFavouriteThemeManager::LoadThemeFolderSchemes(FEdFav_FolderColorTheme& Theme)
{
	FString ThemeData;

	if (Theme.LoadedDefaultColorSchemes.IsEmpty())
	{
		Theme.LoadedDefaultColorSchemes = MakeArrayView<FEdFav_FolderColorScheme>(DefaultFolderColorSchemes, ED_FAV_MAX_COLOR_SCHEMES);
	}
	
	if (FFileHelper::LoadFileToString(ThemeData, *Theme.Filename))
	{
		TSharedRef<TJsonReader<>> ReaderRef = TJsonReaderFactory<>::Create(ThemeData);
		TJsonReader<>& Reader = ReaderRef.Get();

		TSharedPtr<FJsonObject> ObjectPtr;
		if (FJsonSerializer::Deserialize(Reader, ObjectPtr) && ObjectPtr.IsValid())
		{
			// Check that the theme has schemes. We won't load them unless the theme is used
			const TSharedPtr<FJsonObject>* SchemesObject = nullptr;
			if (ObjectPtr->TryGetObjectField(TEXT("Schemes"), SchemesObject))
			{
				for (int32 SchemeIndex = 0; SchemeIndex < ED_FAV_MAX_COLOR_SCHEMES; ++SchemeIndex)
				{
					const TSharedPtr<FJsonObject>* SchemeObject = nullptr;
					if ((*SchemesObject)->TryGetObjectField(FString::FromInt(SchemeIndex), SchemeObject))
					{
						FString ColorString;
						if ((*SchemeObject)->TryGetStringField(TEXT("SchemeColor"), ColorString))
						{
							Theme.LoadedDefaultColorSchemes[SchemeIndex].SchemeColor.InitFromString(ColorString);	
						}
						
						TArray<FString> FolderNames;
						if ((*SchemeObject)->TryGetStringArrayField(TEXT("FolderNames"), FolderNames))
						{
							Theme.LoadedDefaultColorSchemes[SchemeIndex].SaveArrayToFolders(FolderNames);	
						}
						
						TArray<FString> PathNames;
						if ((*SchemeObject)->TryGetStringArrayField(TEXT("ExplicitPaths"), PathNames))
						{
							Theme.LoadedDefaultColorSchemes[SchemeIndex].SaveArrayToPaths(PathNames);	
						}
					}
					SchemeObject = nullptr;
				}
			}
			SchemesObject = nullptr;
		}
	}
}

#if WITH_EDITOR
void UEditorsFavouriteThemeManager::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

#undef LOCTEXT_NAMESPACE
