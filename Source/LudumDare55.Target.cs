// Made by Titled Goose Team during Ludum Dare 55

using UnrealBuildTool;
using System.Collections.Generic;

public class LudumDare55Target : TargetRules
{
	public LudumDare55Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "LudumDare55" } );
	}
}
