// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheGift : ModuleRules
{
	public TheGift(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
