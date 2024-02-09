// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DevFlow : ModuleRules
{
	public DevFlow(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Http" });
		
		PrivateDependencyModuleNames.AddRange(new string[] { "Json", "JsonUtilities" });
		
	}
}
