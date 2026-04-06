#include "Skill.h"



IMPLEMENT_MODULE(FSkillModule, Skill);

void FSkillModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("Skill 모듈이 활성화되었습니다."));
}
void FSkillModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Skill 모듈이 종료되었습니다."));
}