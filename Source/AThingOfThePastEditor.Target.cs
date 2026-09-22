// Copyright GCU 2026. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AThingOfThePastEditorTarget : TargetRules
{
	public AThingOfThePastEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V7;

		ExtraModuleNames.AddRange( new string[] { "AThingOfThePast" } );
	}
}
