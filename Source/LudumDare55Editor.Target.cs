// Made by Titled Goose Team during Ludum Dare 55

using UnrealBuildTool;
using System.Collections.Generic;

public class LudumDare55EditorTarget : TargetRules
{
	public LudumDare55EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "LudumDare55" } );
	}
}
