// Fill out your copyright notice in the Description page of Project Settings.


#include "SKillComponent.h"
#include "SkillDataAsset.h"
#include "SkillBase.h"


void USkillComponent::ActivateSkill(int32 SlotIndex)
{
	UE_LOG(LogTemp, Error, TEXT("Map Size: %d"), SkillMap.Num());
	if (!CanActivateSkill(SlotIndex))
	{
		return;
	}
	
	if (SkillMap.Contains(SlotIndex) && SkillMap[SlotIndex])
	{
		USkillDataAsset* Data = SkillMap[SlotIndex];
		UE_LOG(LogTemp, Error, TEXT("SkillMap Size: %d, Trying to find: %d"), SkillMap.Num(), SlotIndex);
		AActor* Owner = GetOwner();
		if (Owner && Data->SkillClass)
		{
			FActorSpawnParameters Params;
			Params.Owner = Owner;
			Params.Instigator = Owner->GetInstigator();
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			GetWorld()->SpawnActor<AActor>(Data->SkillClass, Owner->GetActorLocation(), Owner->GetActorRotation(), Params);
			SkillCoolTimes.Add(SlotIndex, GetWorld()->GetTimeSeconds());
		}
	}
	
}

bool USkillComponent::CanActivateSkill(int32 SlotIndex)
{
	if (!SkillCoolTimes.Contains(SlotIndex)) return true;
	
	// 마지막 사용시간
	float LastTime = SkillCoolTimes[SlotIndex];
	// 현재시간
	float CurrentTime = GetWorld()->GetTimeSeconds();
	//쿨타임
	float CoolDown = SkillMap[SlotIndex]->CooldownTime;
	
	return (CurrentTime - LastTime) >= CoolDown;
}
