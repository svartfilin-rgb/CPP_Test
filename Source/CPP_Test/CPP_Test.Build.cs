// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CPP_Test : ModuleRules
{
	public CPP_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
                        "Niagara",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CPP_Test",
			"CPP_Test/Variant_Platforming",
			"CPP_Test/Variant_Platforming/Animation",
			"CPP_Test/Variant_Combat",
			"CPP_Test/Variant_Combat/AI",
			"CPP_Test/Variant_Combat/Animation",
			"CPP_Test/Variant_Combat/Gameplay",
			"CPP_Test/Variant_Combat/Interfaces",
			"CPP_Test/Variant_Combat/UI",
			"CPP_Test/Variant_SideScrolling",
			"CPP_Test/Variant_SideScrolling/AI",
			"CPP_Test/Variant_SideScrolling/Gameplay",
			"CPP_Test/Variant_SideScrolling/Interfaces",
			"CPP_Test/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
