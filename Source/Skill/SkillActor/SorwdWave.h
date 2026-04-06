// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "SorwdWave.generated.h"

class UBoxComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class UProjectileMovement;
class UProjectileMovementComponent;
UCLASS()
class SKILL_API ASwordWave : public ASkillBase
{
	GENERATED_BODY()

public:
	ASwordWave();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Projectile")
	TObjectPtr<UBoxComponent> CollisionComp;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Projectile")
	TObjectPtr<UNiagaraSystem>	NiagaraSystem;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Projectile")
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
	
	virtual void OnHit(UPrimitiveComponent* HitComp,
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, 
		const FHitResult& Hit) override;

};
