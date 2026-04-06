// Fill out your copyright notice in the Description page of Project Settings.


#include "SLPlayer.h"
#include "SkillActor/SkillBase.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SkillActor/SKillComponent.h"
// Sets default values
ASLPlayer::ASLPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//방향이동 설정 안함
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	//????
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//스프링암 설정
	//스프링암초기화
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	// 루트 컴포넌트 밑에 설정
	SpringArmComponent->SetupAttachment(RootComponent);
	//??
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	//거리 800
	SpringArmComponent->TargetArmLength = 1100.f;
	//스프링암 회전값 설정
	SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	// 콜리전 없음?
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	// 폰안따라다님
	CameraComponent->bUsePawnControlRotation = false;

	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));
	
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	if (Weapon)
	{
		Weapon->SetupAttachment(RootComponent);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	}
}

void ASLPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TickLerpRollDirection(DeltaSeconds);
}

//롤링 애님실행
void ASLPlayer::PlayRollingMontage(const FRotator& RollRotation)
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (!RollingMontage || PlayerState.bIsRolling || CurrentTime < NextRollingAvailableTime) { return; }

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!IsValid(AnimInstance)) { return; }

	NextRollingAvailableTime = CurrentTime + 5.0f;
	constexpr float RollingSpeed = 2.0f;
	constexpr float RootMotionTranslateScale = 2.5f;

	AnimInstance->Montage_Play(RollingMontage, RollingSpeed);
	SetAnimRootMotionTranslationScale(RootMotionTranslateScale);
	//??
	FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(RollingMontage);
	if (MontageInstance == nullptr) { return; }
	MontageInstance->OnMontageBlendingOutStarted.BindUObject(this, &ThisClass::OnRollMontageBlendedOutStarted);
	PlayerState.bIsRolling = true;
	bLerpRollDirection = true;

	TargetRollRotation = RollRotation;
	RollStartRotation = GetActorRotation();
	RollTime = 0.f;
}

void ASLPlayer::TickLerpRollDirection(float DeltaSeconds)
{
	if (PlayerState.bIsRolling == false || bLerpRollDirection) { return; }

	constexpr float Duration = 0.25f;
	RollTime += DeltaSeconds;

	float const T = RollTime / Duration;
	if (RollTime > Duration)
	{
		bLerpRollDirection = false;
		SetActorRotation(TargetRollRotation);
		return;
	}
	FQuat CurrentQuat = FQuat::Slerp(
		RollStartRotation.Quaternion(),
		TargetRollRotation.Quaternion(),
		T);
	SetActorRotation(CurrentQuat.Rotator());
}

void ASLPlayer::OnRollMontageBlendedOutStarted(UAnimMontage* AnimMontage, bool bInterrupt)
{
	PlayerState.bIsRolling = false;
	bLerpRollDirection = false;
	SetAnimRootMotionTranslationScale(1.0f);
}

void ASLPlayer::UseSkill0()
{
	if (SkillComponent)
	SkillComponent->ActivateSkill(0);
}

void ASLPlayer::UseSkill1()
{
	if (SkillComponent)
	SkillComponent->ActivateSkill(1);
}

void ASLPlayer::UseSkillFromInventory(int32 Index)
{
	if (SkillInventory.IsValidIndex(Index) && SkillInventory[Index])
	{
		const FVector SpawnLocation = GetActorLocation();
		const FRotator SpawnRotation = GetActorRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		
		GetWorld()->SpawnActor<ASkillBase>(SkillInventory[Index], SpawnLocation, SpawnRotation, SpawnParams);
	}
}

