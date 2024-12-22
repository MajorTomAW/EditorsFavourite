// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EditorsFavourite : ModuleRules
{
	public EditorsFavourite(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"InputCore",
				"DeveloperSettings",
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"AssetTools",
				"ContentBrowser",
				"ContentBrowserData",
				"UnrealEd",
				"ToolMenus",
				"Projects",
				"MainFrame",
			});
	}
}
