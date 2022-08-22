// Copyright 2022 Mateusz Michalak. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PongTarget : TargetRules
{
	public PongTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Pong" } );
	}
}
