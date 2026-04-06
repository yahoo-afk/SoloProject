// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SLCharacter.generated.h"

UCLASS()
class SOLOPROJECT_API ASLCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASLCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	int32 MaxHP;
	int32 CurrentHp;
	int32 DefPoint;
	int32 AtkPoint;
	
	//테크 데미지 사용했으니 어플라이 데미지 사용할것
	// virtual float TakeDamage(float DamageAmount,
	// 	struct FDamageEvent const& DamageEvent,
	// 	class AController* EventInstigator, 
	// 	AActor* DamageCauser) override;;
	//
};
