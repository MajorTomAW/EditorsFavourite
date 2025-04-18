// Copyright © 2025 Playton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailPropertyRow;

DECLARE_DELEGATE_OneParam(FOnFolderColorThemeEditorClosed, bool)

class FEdFavFolderColorSchemeCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	//~ Begin IPropertyTypeCustomization Interface
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	//~ End IPropertyTypeCustomization Interface
};

class FEdFavSettingsCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	//~ Begin IDetailCustomization Interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	//~ End IDetailCustomization Interface

	void RefreshComboBox();
	static void PromptToImportTheme(const FString& ImportPath);

protected:
	void MakeThemePickerRow(IDetailPropertyRow& PropertyRow);
	bool IsThemeEditingEnabled() const;
	void GenerateThemeOptions(TSharedPtr<FString>& OutSelectedTheme);
	FReply OnExportThemeClicked(); 
	FReply OnImportThemeClicked(); 
	FReply OnDeleteThemeClicked();
	FReply OnDuplicateAndEditThemeClicked();
	FReply OnEditThemeClicked();
	
	FString GetTextLabelForThemeEntry(TSharedPtr<FString> Entry);
	void OnThemePicked(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
	void OpenThemeEditorWindow(FOnFolderColorThemeEditorClosed OnThemeEditorClosed);

private:
	TArray<TSharedPtr<FString>> ThemeOptions;
	TSharedPtr<STextComboBox> ComboBox;
};