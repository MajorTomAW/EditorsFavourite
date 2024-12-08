// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Classes/Settings/EditorsFavouriteSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEditorsFavouriteSettings() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FDirectoryPath();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FSoftClassPath();
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
EDITORSFAVOURITE_API UClass* Z_Construct_UClass_UEditorsFavouriteSettings();
EDITORSFAVOURITE_API UClass* Z_Construct_UClass_UEditorsFavouriteSettings_NoRegister();
EDITORSFAVOURITE_API UScriptStruct* Z_Construct_UScriptStruct_FEdFav_FolderColorMap();
EDITORSFAVOURITE_API UScriptStruct* Z_Construct_UScriptStruct_FEdFav_FolderColorTheme();
UPackage* Z_Construct_UPackage__Script_EditorsFavourite();
// End Cross Module References

// Begin ScriptStruct FEdFav_FolderColorMap
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_EdFav_FolderColorMap;
class UScriptStruct* FEdFav_FolderColorMap::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_EdFav_FolderColorMap.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_EdFav_FolderColorMap.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEdFav_FolderColorMap, (UObject*)Z_Construct_UPackage__Script_EditorsFavourite(), TEXT("EdFav_FolderColorMap"));
	}
	return Z_Registration_Info_UScriptStruct_EdFav_FolderColorMap.OuterSingleton;
}
template<> EDITORSFAVOURITE_API UScriptStruct* StaticStruct<FEdFav_FolderColorMap>()
{
	return FEdFav_FolderColorMap::StaticStruct();
}
struct Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * FEdFav_FolderColorMap\n *\n * Wrapper struct for customizing the folder color map.\n */" },
#endif
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "FEdFav_FolderColorMap\n\nWrapper struct for customizing the folder color map." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FolderNames_MetaData[] = {
		{ "Category", "ColorMap" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** A list of folder names that will be colored */" },
#endif
		{ "LiveUpdate", "" },
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A list of folder names that will be colored" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FolderPaths_MetaData[] = {
		{ "Category", "ColorMap" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** A list of specific paths that will be colored */" },
#endif
		{ "LiveUpdate", "" },
		{ "LongPackageName", "" },
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
		{ "RelativeToGameContentDir", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A list of specific paths that will be colored" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FolderColor_MetaData[] = {
		{ "Category", "ColorMap" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The color to apply to the appropriate folder names */" },
#endif
		{ "LiveUpdate", "" },
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The color to apply to the appropriate folder names" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_FolderNames_ElementProp;
	static const UECodeGen_Private::FSetPropertyParams NewProp_FolderNames;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FolderPaths_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FolderPaths;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FolderColor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEdFav_FolderColorMap>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::NewProp_FolderNames_ElementProp = { "FolderNames", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FSetPropertyParams Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::NewProp_FolderNames = { "FolderNames", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEdFav_FolderColorMap, FolderNames), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FolderNames_MetaData), NewProp_FolderNames_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::NewProp_FolderPaths_Inner = { "FolderPaths", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDirectoryPath, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::NewProp_FolderPaths = { "FolderPaths", nullptr, (EPropertyFlags)0x0010040000010001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEdFav_FolderColorMap, FolderPaths), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FolderPaths_MetaData), NewProp_FolderPaths_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::NewProp_FolderColor = { "FolderColor", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEdFav_FolderColorMap, FolderColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FolderColor_MetaData), NewProp_FolderColor_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::NewProp_FolderNames_ElementProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::NewProp_FolderNames,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::NewProp_FolderPaths_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::NewProp_FolderPaths,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::NewProp_FolderColor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_EditorsFavourite,
	nullptr,
	&NewStructOps,
	"EdFav_FolderColorMap",
	Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::PropPointers),
	sizeof(FEdFav_FolderColorMap),
	alignof(FEdFav_FolderColorMap),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEdFav_FolderColorMap()
{
	if (!Z_Registration_Info_UScriptStruct_EdFav_FolderColorMap.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_EdFav_FolderColorMap.InnerSingleton, Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_EdFav_FolderColorMap.InnerSingleton;
}
// End ScriptStruct FEdFav_FolderColorMap

// Begin ScriptStruct FEdFav_FolderColorTheme
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_EdFav_FolderColorTheme;
class UScriptStruct* FEdFav_FolderColorTheme::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_EdFav_FolderColorTheme.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_EdFav_FolderColorTheme.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEdFav_FolderColorTheme, (UObject*)Z_Construct_UPackage__Script_EditorsFavourite(), TEXT("EdFav_FolderColorTheme"));
	}
	return Z_Registration_Info_UScriptStruct_EdFav_FolderColorTheme.OuterSingleton;
}
template<> EDITORSFAVOURITE_API UScriptStruct* StaticStruct<FEdFav_FolderColorTheme>()
{
	return FEdFav_FolderColorTheme::StaticStruct();
}
struct Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * FEdFav_FolderColorTheme\n *\n * Wrapper struct for customizing the EditorsFavourite settings.\n */" },
#endif
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "FEdFav_FolderColorTheme\n\nWrapper struct for customizing the EditorsFavourite settings." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProfileName_MetaData[] = {
		{ "Category", "Profile" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The name of the profile */" },
#endif
		{ "EditCondition", "bIsCustomProfile" },
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The name of the profile" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FolderBlacklist_MetaData[] = {
		{ "Category", "Profile" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** List of folders to ignore */" },
#endif
		{ "LiveUpdate", "" },
		{ "LongPackageName", "" },
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
		{ "RelativeToGameContentDir", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "List of folders to ignore" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FolderColorMaps_MetaData[] = {
		{ "Category", "Profile" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The folder color map */" },
#endif
		{ "LiveUpdate", "" },
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The folder color map" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsCustomProfile_MetaData[] = {
		{ "Category", "EdFav_FolderColorTheme" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** This allows the profile to be renamed or deleted */" },
#endif
		{ "EditCondition", "FALSE" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "This allows the profile to be renamed or deleted" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ProfileName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FolderBlacklist_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FolderBlacklist;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FolderColorMaps_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FolderColorMaps;
	static void NewProp_bIsCustomProfile_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsCustomProfile;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEdFav_FolderColorTheme>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_ProfileName = { "ProfileName", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEdFav_FolderColorTheme, ProfileName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProfileName_MetaData), NewProp_ProfileName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_FolderBlacklist_Inner = { "FolderBlacklist", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FDirectoryPath, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_FolderBlacklist = { "FolderBlacklist", nullptr, (EPropertyFlags)0x0010040000010001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEdFav_FolderColorTheme, FolderBlacklist), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FolderBlacklist_MetaData), NewProp_FolderBlacklist_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_FolderColorMaps_Inner = { "FolderColorMaps", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FEdFav_FolderColorMap, METADATA_PARAMS(0, nullptr) }; // 1178637181
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_FolderColorMaps = { "FolderColorMaps", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEdFav_FolderColorTheme, FolderColorMaps), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FolderColorMaps_MetaData), NewProp_FolderColorMaps_MetaData) }; // 1178637181
void Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_bIsCustomProfile_SetBit(void* Obj)
{
	((FEdFav_FolderColorTheme*)Obj)->bIsCustomProfile = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_bIsCustomProfile = { "bIsCustomProfile", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(FEdFav_FolderColorTheme), &Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_bIsCustomProfile_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsCustomProfile_MetaData), NewProp_bIsCustomProfile_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_ProfileName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_FolderBlacklist_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_FolderBlacklist,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_FolderColorMaps_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_FolderColorMaps,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewProp_bIsCustomProfile,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_EditorsFavourite,
	nullptr,
	&NewStructOps,
	"EdFav_FolderColorTheme",
	Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::PropPointers),
	sizeof(FEdFav_FolderColorTheme),
	alignof(FEdFav_FolderColorTheme),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEdFav_FolderColorTheme()
{
	if (!Z_Registration_Info_UScriptStruct_EdFav_FolderColorTheme.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_EdFav_FolderColorTheme.InnerSingleton, Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_EdFav_FolderColorTheme.InnerSingleton;
}
// End ScriptStruct FEdFav_FolderColorTheme

// Begin Class UEditorsFavouriteSettings
void UEditorsFavouriteSettings::StaticRegisterNativesUEditorsFavouriteSettings()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UEditorsFavouriteSettings);
UClass* Z_Construct_UClass_UEditorsFavouriteSettings_NoRegister()
{
	return UEditorsFavouriteSettings::StaticClass();
}
struct Z_Construct_UClass_UEditorsFavouriteSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * UEditorsFavouriteSettings\n *\n * Settings class for the EditorsFavourite module.\n */" },
#endif
		{ "IncludePath", "Settings/EditorsFavouriteSettings.h" },
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UEditorsFavouriteSettings\n\nSettings class for the EditorsFavourite module." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLiveUpdateFolderColors_MetaData[] = {
		{ "Category", "Content Browser" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether to live update the folder colors */" },
#endif
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to live update the folder colors" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bClearBlacklistedFolderColors_MetaData[] = {
		{ "Category", "Content Browser" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether to clear the color of the blacklisted folders */" },
#endif
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to clear the color of the blacklisted folders" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bColorizePluginFolders_MetaData[] = {
		{ "Category", "Content Browser" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether to also colorize the folders that are inside plugins */" },
#endif
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to also colorize the folders that are inside plugins" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FolderColorTheme_MetaData[] = {
		{ "Category", "Content Browser" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The default profile */" },
#endif
		{ "LiveUpdate", "" },
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The default profile" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CommonClasses_MetaData[] = {
		{ "AllowAbstract", "" },
		{ "Category", "Blueprint Class Picker" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** List of classes that are common in the blueprint class dialog */" },
#endif
		{ "ModuleRelativePath", "Classes/Settings/EditorsFavouriteSettings.h" },
		{ "SaveImmediately", "" },
		{ "ShowTreeView", "TRUE" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "List of classes that are common in the blueprint class dialog" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_bLiveUpdateFolderColors_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLiveUpdateFolderColors;
	static void NewProp_bClearBlacklistedFolderColors_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bClearBlacklistedFolderColors;
	static void NewProp_bColorizePluginFolders_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bColorizePluginFolders;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FolderColorTheme;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CommonClasses_ElementProp;
	static const UECodeGen_Private::FSetPropertyParams NewProp_CommonClasses;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEditorsFavouriteSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
void Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bLiveUpdateFolderColors_SetBit(void* Obj)
{
	((UEditorsFavouriteSettings*)Obj)->bLiveUpdateFolderColors = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bLiveUpdateFolderColors = { "bLiveUpdateFolderColors", nullptr, (EPropertyFlags)0x0020080000014001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UEditorsFavouriteSettings), &Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bLiveUpdateFolderColors_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLiveUpdateFolderColors_MetaData), NewProp_bLiveUpdateFolderColors_MetaData) };
void Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bClearBlacklistedFolderColors_SetBit(void* Obj)
{
	((UEditorsFavouriteSettings*)Obj)->bClearBlacklistedFolderColors = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bClearBlacklistedFolderColors = { "bClearBlacklistedFolderColors", nullptr, (EPropertyFlags)0x0020080000014001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UEditorsFavouriteSettings), &Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bClearBlacklistedFolderColors_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bClearBlacklistedFolderColors_MetaData), NewProp_bClearBlacklistedFolderColors_MetaData) };
void Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bColorizePluginFolders_SetBit(void* Obj)
{
	((UEditorsFavouriteSettings*)Obj)->bColorizePluginFolders = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bColorizePluginFolders = { "bColorizePluginFolders", nullptr, (EPropertyFlags)0x0020080000014001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UEditorsFavouriteSettings), &Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bColorizePluginFolders_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bColorizePluginFolders_MetaData), NewProp_bColorizePluginFolders_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_FolderColorTheme = { "FolderColorTheme", nullptr, (EPropertyFlags)0x0020080000014001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEditorsFavouriteSettings, FolderColorTheme), Z_Construct_UScriptStruct_FEdFav_FolderColorTheme, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FolderColorTheme_MetaData), NewProp_FolderColorTheme_MetaData) }; // 155858239
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_CommonClasses_ElementProp = { "CommonClasses", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FSoftClassPath, METADATA_PARAMS(0, nullptr) };
static_assert(TModels_V<CGetTypeHashable, FSoftClassPath>, "The structure 'FSoftClassPath' is used in a TSet but does not have a GetValueTypeHash defined");
const UECodeGen_Private::FSetPropertyParams Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_CommonClasses = { "CommonClasses", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEditorsFavouriteSettings, CommonClasses), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CommonClasses_MetaData), NewProp_CommonClasses_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UEditorsFavouriteSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bLiveUpdateFolderColors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bClearBlacklistedFolderColors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_bColorizePluginFolders,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_FolderColorTheme,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_CommonClasses_ElementProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEditorsFavouriteSettings_Statics::NewProp_CommonClasses,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEditorsFavouriteSettings_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UEditorsFavouriteSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_EditorsFavourite,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEditorsFavouriteSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UEditorsFavouriteSettings_Statics::ClassParams = {
	&UEditorsFavouriteSettings::StaticClass,
	"Editor",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UEditorsFavouriteSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UEditorsFavouriteSettings_Statics::PropPointers),
	0,
	0x000000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEditorsFavouriteSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UEditorsFavouriteSettings_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UEditorsFavouriteSettings()
{
	if (!Z_Registration_Info_UClass_UEditorsFavouriteSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEditorsFavouriteSettings.OuterSingleton, Z_Construct_UClass_UEditorsFavouriteSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UEditorsFavouriteSettings.OuterSingleton;
}
template<> EDITORSFAVOURITE_API UClass* StaticClass<UEditorsFavouriteSettings>()
{
	return UEditorsFavouriteSettings::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UEditorsFavouriteSettings);
UEditorsFavouriteSettings::~UEditorsFavouriteSettings() {}
// End Class UEditorsFavouriteSettings

// Begin Registration
struct Z_CompiledInDeferFile_FID_Unreal_Projects_Botanibots_BotanibotsGame_Plugins_Editor_EditorsFavourite_Source_Classes_Settings_EditorsFavouriteSettings_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FEdFav_FolderColorMap::StaticStruct, Z_Construct_UScriptStruct_FEdFav_FolderColorMap_Statics::NewStructOps, TEXT("EdFav_FolderColorMap"), &Z_Registration_Info_UScriptStruct_EdFav_FolderColorMap, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEdFav_FolderColorMap), 1178637181U) },
		{ FEdFav_FolderColorTheme::StaticStruct, Z_Construct_UScriptStruct_FEdFav_FolderColorTheme_Statics::NewStructOps, TEXT("EdFav_FolderColorTheme"), &Z_Registration_Info_UScriptStruct_EdFav_FolderColorTheme, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEdFav_FolderColorTheme), 155858239U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UEditorsFavouriteSettings, UEditorsFavouriteSettings::StaticClass, TEXT("UEditorsFavouriteSettings"), &Z_Registration_Info_UClass_UEditorsFavouriteSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEditorsFavouriteSettings), 1883668717U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_Botanibots_BotanibotsGame_Plugins_Editor_EditorsFavourite_Source_Classes_Settings_EditorsFavouriteSettings_h_4150868931(TEXT("/Script/EditorsFavourite"),
	Z_CompiledInDeferFile_FID_Unreal_Projects_Botanibots_BotanibotsGame_Plugins_Editor_EditorsFavourite_Source_Classes_Settings_EditorsFavouriteSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_Botanibots_BotanibotsGame_Plugins_Editor_EditorsFavourite_Source_Classes_Settings_EditorsFavouriteSettings_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Unreal_Projects_Botanibots_BotanibotsGame_Plugins_Editor_EditorsFavourite_Source_Classes_Settings_EditorsFavouriteSettings_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_Botanibots_BotanibotsGame_Plugins_Editor_EditorsFavourite_Source_Classes_Settings_EditorsFavouriteSettings_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
