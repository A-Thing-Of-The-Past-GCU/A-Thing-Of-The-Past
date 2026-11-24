// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TDT : ModuleRules
{
	public TDT(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"GameplayTags",
				"InputCore",
				"SlateCore",
				"Slate",
				"Engine",
				"UMG", 
				"CommonUI",
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",

				"DeveloperSettings",
			}
		);
	}
}
