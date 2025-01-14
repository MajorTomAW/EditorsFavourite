// Copyright © 2024 Botanibots Team. All rights reserved.


#include "EditorsFavouriteSettings.h"
#include "EditorFolderUtils.h"
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"

#define LOCTEXT_NAMESPACE "EditorsFavourite"

FEdFav_FolderColorTheme::FEdFav_FolderColorTheme()
	: bIsCustomProfile(true)
{
}




UEditorsFavouriteSettings::UEditorsFavouriteSettings()
	: bLiveUpdateFolderColors(true)
	, bClearBlacklistedFolderColors(false)
	, bColorizePluginFolders(true)
	, bOverrideBlueprintClassPicker(false)
{
	SectionName = FName(TEXT("EditorsFavourite"));

	FolderColorTheme = FEdFav_FolderColorTheme(false, TEXT("Default"));
}

FName UEditorsFavouriteSettings::GetContainerName() const
{
	return FName(TEXT("Editor"));
}

FName UEditorsFavouriteSettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}

#if WITH_EDITOR
FText UEditorsFavouriteSettings::GetSectionText() const
{
	return LOCTEXT("SettingsLabel", "Editor's Favourite");
}

FText UEditorsFavouriteSettings::GetSectionDescription() const
{
	return LOCTEXT("SettingsDescription", "Editor's Favourite settings");
}
#endif

void UEditorsFavouriteSettings::PostLoad()
{
	Super::PostLoad();
}

void UEditorsFavouriteSettings::PostInitProperties()
{
	Super::PostInitProperties();

	if (!bOverrideBlueprintClassPicker)
	{
		return;
	}

	if (!GUnrealEd)
	{
		return;
	}

	FCoreDelegates::OnPostEngineInit.AddLambda([this]()
	{
		// Load Common Classes
		if (UUnrealEdOptions* UnrealEdOptions = GUnrealEd->GetUnrealEdOptions())
		{
			for (const FClassPickerDefaults& Default : UnrealEdOptions->NewAssetDefaultClasses)
			{
				CommonClasses.Add(Default.ClassName);
			}

			UnrealEdOptions->bExpandClassPickerClassList = true;
		}
	});
}

void UEditorsFavouriteSettings::SaveEditorsFavouriteConfig(bool bSaveGlobal)
{
	UEditorsFavouriteSettings* MutableThis = Get();

	FString DefaultEditorIni = FPaths::SourceConfigDir() / TEXT("DefaultEditor.ini");
	DefaultEditorIni = FConfigCacheIni::NormalizeConfigIniPath(DefaultEditorIni);
	MutableThis->SaveConfig(CPF_Config, *DefaultEditorIni);


	// Save Common Classes if Blueprint Class Picker is overriden
	if (!MutableThis->bOverrideBlueprintClassPicker)
	{
		return;
	}

	// Save Common Classes
	TArray<FClassPickerDefaults>& Defaults = GUnrealEd->GetUnrealEdOptions()->NewAssetDefaultClasses;
	Defaults.Empty();
	for (const FSoftClassPath& Path : MutableThis->CommonClasses.Array())
	{
		if (Path.IsNull()) continue;

		const FString ClassName = Path.GetAssetPathString();
		const FString AssetClass = TEXT("/Script/Engine.Blueprint");
		Defaults.Add(FClassPickerDefaults(ClassName, AssetClass));
	}

	GUnrealEd->GetUnrealEdOptions()->SaveConfig(CPF_Config, *DefaultEditorIni);

	const FString Section = TEXT("/Script/UnrealEd.UnrealEdOptions");
	GConfig->SetString(*Section, TEXT("!NewAssetDefaultClasses"), TEXT("ClearArray"), DefaultEditorIni);
}

bool UEditorsFavouriteSettings::GetFolderColor(const FString& FolderPath, FLinearColor& OutColor) const
{
	for (const auto& FolderColorMap : FolderColorTheme.FolderColorMaps)
	{
		for (const FString& Folder : FolderColorMap.FolderNames)
		{
			if (
				(Folder == FolderPath) ||
				(FEditorFolderUtils::GetLeafName(FName(*FolderPath)) == FName(*Folder))
				)
			{
				OutColor = FolderColorMap.FolderColor;
				return true;
			}
		}
	}

	return false;
}

bool UEditorsFavouriteSettings::IsFolderInBlacklist(const FString& FolderPath) const
{
	for (const auto& Path : FolderColorTheme.FolderBlacklist)
	{
		if (Path.Path.Contains(FolderPath))
		{
			return true;
		}

		if (FolderPath.StartsWith(Path.Path))
		{
			return true;
		}

		/*if (FEditorFolderUtils::PathIsChildOf(FolderPath, Path.Path))
		{
			return true;
		}*/
	}

	return false;
}

#if WITH_EDITOR
void UEditorsFavouriteSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property == nullptr)
	{
		return;
	}
	
	auto IsSaveImmediately = [](const FProperty* Property)
	{
		return Property->HasMetaData("SaveImmediately") ||
			Property->GetOwnerProperty()->HasMetaData("SaveImmediately");
	};

	auto IsLiveUpdate = [](const FProperty* Property)
	{
		return Property->HasMetaData("LiveUpdate") ||
			Property->GetOwnerProperty()->HasMetaData("LiveUpdate");
	};

	auto IsProperty = [](const FPropertyChangedEvent& InEvent, const FName InPropertyName)
	{
		return (InEvent.Property->GetFName() == InPropertyName) ||
			(InEvent.MemberProperty->GetFName() == InPropertyName) ||
			(InEvent.MemberProperty->GetOwnerProperty()->GetFName() == InPropertyName);
	};

	if (IsSaveImmediately(PropertyChangedEvent.Property))
	{
		SaveEditorsFavouriteConfig();
	}

	if ((
			IsLiveUpdate(PropertyChangedEvent.Property) ||
			IsLiveUpdate(PropertyChangedEvent.MemberProperty) ||
			IsLiveUpdate(PropertyChangedEvent.MemberProperty->GetOwnerProperty())
		) && bLiveUpdateFolderColors)
	{
		RequestLiveUpdateDelegate.Broadcast(this);
	}

	if (IsProperty(PropertyChangedEvent, GET_MEMBER_NAME_CHECKED(UEditorsFavouriteSettings, CommonClasses)))
	{
		SaveEditorsFavouriteConfig();
	}
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

#undef LOCTEXT_NAMESPACE
