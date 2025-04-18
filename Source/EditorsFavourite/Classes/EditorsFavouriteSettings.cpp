// Copyright © 2025 MajorT. All Rights Reserved.


#include "EditorsFavouriteSettings.h"

#include "EditorsFavouriteThemeManager.h"
#include "Interfaces/IPluginManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EditorsFavouriteSettings)

#define LOCTEXT_NAMESPACE "EditorsFavourite"

UEditorsFavouriteSettings::UEditorsFavouriteSettings()
{
	CategoryName = FApp::GetProjectName();
	SectionName = TEXT("EditorsFavourite");
}

void UEditorsFavouriteSettings::Init()
{
	if (CurrentAppliedTheme.IsValid())
	{
		UEditorsFavouriteThemeManager::Get().ApplyTheme(CurrentAppliedTheme);
	}
	else
	{
		CurrentAppliedTheme = UEditorsFavouriteThemeManager::Get().GetCurrentThemeID();
		SaveConfig();
	}

	UEditorsFavouriteThemeManager::Get().ApplyTheme(UEditorsFavouriteThemeManager::Get().GetCurrentTheme().Id);
}

void UEditorsFavouriteSettings::PostLoad()
{
	Super::PostLoad();
}

FName UEditorsFavouriteSettings::GetContainerName() const
{
	return FName(TEXT("Editor"));
}

#if WITH_EDITOR
FText UEditorsFavouriteSettings::GetSectionText() const
{
	return LOCTEXT("SectionText", "Editor's Favourite");
}

FText UEditorsFavouriteSettings::GetSectionDescription() const
{
	return LOCTEXT("SectionDescription", "Settings for the Editors Favourite plugin");
}

void UEditorsFavouriteSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if (PropertyChangedEvent.Property == nullptr)
	{
		return;
	}

	// Helper lambda to check if a property has the LiveUpdate metadata.
	auto IsLiveUpdate = [PropertyChangedEvent]()
	{
		return PropertyChangedEvent.Property->HasMetaData("LiveUpdate") ||
			PropertyChangedEvent.Property->GetOwnerProperty()->HasMetaData("LiveUpdate") ||
			PropertyChangedEvent.MemberProperty->HasMetaData("LiveUpdate");
	};

	// Request a live update if the property has the LiveUpdate metadata.
	if (IsLiveUpdate() && ShouldLiveUpdateFolders())
	{
		OnRequestLiveUpdate.Broadcast(this);
	}
}
#endif

#undef LOCTEXT_NAMESPACE
