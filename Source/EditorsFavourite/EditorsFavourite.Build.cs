// Copyright © 2025 MajorT. All Rights Reserved.

using UnrealBuildTool;

public class EditorsFavourite : ModuleRules
{
	public EditorsFavourite(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new []
		{ 
			"Json",
			"JsonUtilities",
			"Core", 
			"InputCore", 
			"DeveloperSettings",
		});
			
		
		PrivateDependencyModuleNames.AddRange(new []
		{ 
			"CoreUObject", 
			"Engine", 
			"Slate", 
			"SlateCore", 
			"AssetTools", 
			"ToolWidgets",
			"ContentBrowser", 
			"ContentBrowserData", 
			"UnrealEd", 
			"ToolMenus", 
			"Projects", 
			"MainFrame",
			"SettingsEditor",
		});
	}
}
