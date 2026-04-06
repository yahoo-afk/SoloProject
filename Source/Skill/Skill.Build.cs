using UnrealBuildTool;

// 모듈을 상속받는 스킬을 마듬
public class Skill : ModuleRules
{
	public Skill(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.AddRange(new string[] { "Skill" });
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore","Niagara",
		});
		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
    