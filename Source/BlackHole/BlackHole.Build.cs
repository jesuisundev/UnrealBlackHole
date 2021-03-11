// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BlackHole : ModuleRules
{
	public BlackHole(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
