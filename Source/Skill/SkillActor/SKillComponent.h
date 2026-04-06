// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SKillComponent.generated.h"

class USkillDataAsset;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SKILL_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Skills")
	TMap<int32, USkillDataAsset*> SkillMap;
	
	TMap<int32, float> SkillCoolTimes;
	
	bool CanActivateSkill(int32 SlotIndex);
	void ActivateSkill(int32 SlotIndex);
};
