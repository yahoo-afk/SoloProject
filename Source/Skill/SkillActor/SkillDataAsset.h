// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillDataAsset.generated.h"


/**
 * 
 */
UCLASS()
class SKILL_API USkillDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Logic")
	TSubclassOf<class ASkillBase> SkillClass;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float CooldownTime;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Damager;
};
