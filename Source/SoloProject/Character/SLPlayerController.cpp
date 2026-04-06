// Fill out your copyright notice in the Description page of Project Settings.


#include "SLPlayerController.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/SPIRV-Headers/include/spirv/unified1/spirv.h>

#include "SLPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "SkillActor/SKillComponent.h"


ASLPlayerController::ASLPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ASLPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SkillComp = Cast<USkillComponent>(GetPawn()->GetComponentByClass(USkillComponent::StaticClass()));
}

void ASLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		//0번째 컨트롤러로 사용하겠다
		SubSystem->AddMappingContext(DefaultMappingContext,0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveInputAction,ETriggerEvent::Started,this,&ASLPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(MoveInputAction,ETriggerEvent::Triggered,this,&ASLPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(MoveInputAction,ETriggerEvent::Completed,this,&ASLPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(MoveInputAction,ETriggerEvent::Canceled,this,&ASLPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(RollingAction,ETriggerEvent::Started,this,&ASLPlayerController::RequestRolling);
		//EnhancedInputComponent->BindAction(AttackAction,ETriggerEvent::Started,this,&ASLPlayerController::OnAttack);
		//EnhancedInputComponent->BindAction(DashAttackAction,ETriggerEvent::Started,this,&ASLPlayerController::OnBlinkStrikeAttack);
		EnhancedInputComponent->BindAction(SkillAction0,ETriggerEvent::Started,this,&ASLPlayerController::OnSkill0Triggered);
		EnhancedInputComponent->BindAction(SkillAction1,ETriggerEvent::Started,this,&ASLPlayerController::OnSkill1Triggered);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Red,FString(TEXT("오류발생")));
		}
	}
}


void ASLPlayerController::OnInputStarted()
{
	StopMovement();
}

void ASLPlayerController::OnSetDestinationTriggered()
{
	StopMovement();
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	FHitResult Hit;
	bool bHitSuccess = false;
	bHitSuccess = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccess)
	{
		CachedDestination = Hit.Location;
	}
	
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection,1.0,false);
		
		//??
		const FRotator DesiredRotation = WorldDirection.GetSafeNormal2D().Rotation();
		SetControlRotation(DesiredRotation);
	}
}

void ASLPlayerController::OnSetDestinationReleased()
{
	StopMovement();
	if (FollowTime <= ShortPressThreshold)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,CachedDestination);
	}
	FollowTime = 0.f;
}

void ASLPlayerController::RequestRolling()
{
	if (ASLPlayer* SLPlayer = Cast<ASLPlayer>(GetPawn()))
	{
		StopMovement();
		SLPlayer->PlayRollingMontage(GetDesiredRotation());
	}
}


void ASLPlayerController::OnSkill0Triggered()
{
	StopMovement();
	if (ASLPlayer* SLPlayer = Cast<ASLPlayer>(GetPawn()))
	{
		if (SLPlayer)
		SLPlayer->UseSkill0();
	}
}

void ASLPlayerController::OnSkill1Triggered()
{
	StopMovement();

	if (ASLPlayer* SLPlayer = Cast<ASLPlayer>(GetPawn()))
	{
		if (SLPlayer)
		{
			SLPlayer->UseSkill1();
		}
	}
}
