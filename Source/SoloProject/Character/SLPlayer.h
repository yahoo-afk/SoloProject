// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SLCharacter.h"
#include "SLPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ASkillBase;
class USkillComponent;
struct FCharacterState
{
	FCharacterState()
	{
	
	}
	bool bIsRolling = false;
	bool bIsAttacking = false;
	
};


UCLASS()
class SOLOPROJECT_API ASLPlayer : public ASLCharacter
{
	GENERATED_BODY()
public:
	ASLPlayer();
	virtual void Tick(float DeltaSeconds) override;;

	void PlayRollingMontage(const FRotator& RollRotation);
	
	void TickLerpRollDirection(float DeltaSeconds);
	
	void OnRollMontageBlendedOutStarted(UAnimMontage* AnimMontage, bool bInterrupt);
	
	void UseSkill0();
	void UseSkill1();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TArray<TSubclassOf<ASkillBase>> SkillInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TSubclassOf<ASkillBase> EquippedSkill;
	UFUNCTION()
	void UseSkillFromInventory(int32 Index);
	
	UCameraComponent* GetTopDownCameraComponent() const { return CameraComponent; }
	USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))	
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Weapon;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Montage",meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage>RollingMontage;
	
	//구르기
	FCharacterState PlayerState;
	// 보간함수에 사용할방향
	bool bLerpRollDirection = false;
	//
	float RollTime = 0.f;
	
	FRotator RollStartRotation;
	
	FRotator TargetRollRotation;
	
	float NextRollingAvailableTime = 0.f;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill",meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASkillBase> SwordWaveClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill",meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASkillBase> BlinkStrikeAttack;
	
public:
	// 검기
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input",meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkillComponent> SkillComponent;
};
