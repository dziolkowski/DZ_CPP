// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DZ_CPP : ModuleRules
{
	public DZ_CPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"DZ_CPP",
			"DZ_CPP/Variant_Platforming",
			"DZ_CPP/Variant_Platforming/Animation",
			"DZ_CPP/Variant_Combat",
			"DZ_CPP/Variant_Combat/AI",
			"DZ_CPP/Variant_Combat/Animation",
			"DZ_CPP/Variant_Combat/Gameplay",
			"DZ_CPP/Variant_Combat/Interfaces",
			"DZ_CPP/Variant_Combat/UI",
			"DZ_CPP/Variant_SideScrolling",
			"DZ_CPP/Variant_SideScrolling/AI",
			"DZ_CPP/Variant_SideScrolling/Gameplay",
			"DZ_CPP/Variant_SideScrolling/Interfaces",
			"DZ_CPP/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
