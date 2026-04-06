// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "SLPlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class USkillComponent;
UCLASS()
class SOLOPROJECT_API ASLPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASLPlayerController();
	
	//누른 시간
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Input)
	float ShortPressThreshold;
	
	//클릭시 이펙트
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Input)
	UNiagaraSystem* FXCursor;
	
	//맵핑컨텍스트
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Input,meta=(AllowPrivateAccess=true))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Input,meta=(AllowPrivateAccess=true))
	UInputAction* MoveInputAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Input,meta=(AllowPrivateAccess=true))
	UInputAction* RollingAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Input,meta=(AllowPrivateAccess=true))
	UInputAction* SkillAction0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Input,meta=(AllowPrivateAccess=true))
	UInputAction* SkillAction1;
	
	USkillComponent* SkillComp;
protected:
	uint32 bMoveToMouseCursor : 1;
	
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void RequestRolling();

	//void OnAttack();
	
	//void OnBlinkStrikeAttack();
	
	void OnSkill0Triggered();
	void OnSkill1Triggered();
	
private:
	FVector CachedDestination;
	
	float FollowTime;
};