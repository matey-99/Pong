// Copyright 2022 Mateusz Michalak. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PongEditorTarget : TargetRules
{
	public PongEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Pong" } );
	}
}
