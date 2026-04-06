// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "ABlinkStrike.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class ACharacter;

UCLASS()
class SKILL_API ABlinkStrike : public ASkillBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlinkStrike();
	TArray<FVector> DashSkill();
	UPROPERTY()
	ACharacter* TargetCharacter;	
	
	TArray<FVector> DashPoints;
	
	int32 CurrentIndex=0;
	
	FTimerHandle DashTimerHandle;
	
	bool bIsUsing =false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "DashSkill")
	float SearchEnemyRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "DashSkill")
	float StopOffset;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Effect")
	TObjectPtr<UNiagaraSystem>	NiagaraSystem;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Effect")
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
	
	void MovePointNextPoint();
	void MoveTargetCharacter(ACharacter* Character,const TArray<FVector>& DashLocationPoint);
	void PlayDashEffect(const FVector& Location);
};
