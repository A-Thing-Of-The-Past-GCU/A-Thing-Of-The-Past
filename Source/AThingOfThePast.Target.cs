// Copyright GCU 2026. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AThingOfThePastTarget : TargetRules
{
	public AThingOfThePastTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V7;

		ExtraModuleNames.AddRange( new string[] { "AThingOfThePast" } );
	}
}
