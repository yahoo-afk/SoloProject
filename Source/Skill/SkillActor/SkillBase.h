// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillBase.generated.h"



UCLASS()
class SKILL_API ASkillBase : public AActor
{
	GENERATED_BODY()
public:
	ASkillBase();
	//스킬 주인 지정
	void InitializeSkill(AActor* InOwner) { OwnerActor = InOwner; }
protected:
	// 누가 스킬주인가?
	UPROPERTY(BlueprintReadOnly, Category = "Skill")
	TObjectPtr<AActor> OwnerActor;
	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, 
		const FHitResult& Hit){};
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Skil")
	float CoolDown;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Skil")
	float Damage;
};
