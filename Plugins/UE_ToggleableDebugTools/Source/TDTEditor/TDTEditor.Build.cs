using UnrealBuildTool;

public class TDTEditor : ModuleRules
{
    public TDTEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "UMG",
                "Blutility",
                "UMGEditor",
                "AssetRegistry",
                "UnrealEd",
                "EditorScriptingUtilities",
                "BlueprintGraph",
                "StructUtils",
                
                
                "Projects", 

                "ToolMenus",
                "Engine",
                "Slate",
                "SlateCore",
            }
        );
    }
}