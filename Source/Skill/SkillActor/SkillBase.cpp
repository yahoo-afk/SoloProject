// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"


// Sets default values
ASkillBase::ASkillBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CoolDown = 0.0f;
	Damage = 0.0f;
}


