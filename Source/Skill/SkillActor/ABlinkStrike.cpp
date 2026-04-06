// Fill out your copyright notice in the Description page of Project Settings.


#include "ABlinkStrike.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values


ABlinkStrike::ABlinkStrike()
{
	//생성자에서 초기화
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;
	SearchEnemyRange = 1000.f;
	StopOffset = 150.f;
	NiagaraComponent =CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment((RootComponent));
	TargetCharacter = CreateDefaultSubobject<ACharacter>(TEXT("TargetCharacter"));
	
	Damage =20;
}

// 주변정보 수집
TArray<FVector> ABlinkStrike::DashSkill()
{
	TArray<FVector> DashPoint;
	AActor* SkillOwner = GetOwner();
	if (!IsValid(SkillOwner))
	{
		return DashPoint ;
	}
	
	TArray<FOverlapResult> OverlapActors;
	const FCollisionShape  Sphere = FCollisionShape::MakeSphere(SearchEnemyRange);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(SkillOwner);
	
	GetWorld()->OverlapMultiByChannel(
		OverlapActors,
		SkillOwner->GetActorLocation(),
		FQuat::Identity,
		ECC_Pawn,
		Sphere,
		Params);
	
	for (const FOverlapResult& Result : OverlapActors)
	{
		AActor* FoundActor = Result.GetActor();
		if (IsValid(FoundActor)&&FoundActor->ActorHasTag(TEXT("Monster")))
		{
			// 몬스터의 위치
			const float BackDistance =120.f;
			FVector MonsterLocation	 = FoundActor->GetActorLocation();
			// 몬스터가 바라보는 방향의 위치
			const FVector MonsterFWV = FoundActor->GetActorForwardVector();
			// 몬스터의 위치에서 뒤로 120만큼 이동
			const FVector TargetLocation = MonsterLocation - (MonsterFWV * BackDistance);
			DashPoint.Add(TargetLocation);
			
			UGameplayStatics::ApplyDamage(
			FoundActor,          
			 Damage,        
			 SkillOwner->GetInstigatorController(),
			 SkillOwner,           
			 UDamageType::StaticClass()
		  );
		}
	}
	return DashPoint;
}
void ABlinkStrike::MoveTargetCharacter(ACharacter* Target,const TArray<FVector>& DashLocationPoint)
{
	TargetCharacter = Target;
	DashPoints = DashLocationPoint;
	CurrentIndex = 0;
	if (IsValid(TargetCharacter)&&DashPoints.Num() > 0)
	{
		MovePointNextPoint();
	}
}

void ABlinkStrike::MovePointNextPoint()
{
	if (!TargetCharacter || !DashPoints.IsValidIndex(CurrentIndex))
	{
		Destroy();
		return;
	}
	
	FVector NextLocation = DashPoints[CurrentIndex];
	TargetCharacter->SetActorLocation(NextLocation);
	
	FVector LookDirection = (NextLocation - TargetCharacter->GetActorLocation()).GetSafeNormal();
	FRotator BackRotation = (-LookDirection).Rotation(); 
	BackRotation.Pitch = 0.f;
	BackRotation.Roll = 0.f;
	
	TargetCharacter->SetActorRotation(BackRotation);
	PlayDashEffect(DashPoints[CurrentIndex]);
	CurrentIndex++;
	GetWorldTimerManager().SetTimer(DashTimerHandle,this,&ABlinkStrike::MovePointNextPoint,0.5,false);
	
}
// 이펙트 생길 위치결정
void ABlinkStrike::PlayDashEffect(const FVector& Location)
{
	SetActorLocation(Location);
	if (NiagaraComponent)
	{
		if (NiagaraSystem) 
		{	
			NiagaraComponent->SetAsset(NiagaraSystem); 
		}
		NiagaraComponent->Activate(true); 
	}
}

void ABlinkStrike::BeginPlay()
{
	Super::BeginPlay();
	AActor* MyOwner = GetOwner();
	
	if (MyOwner == nullptr) 
	{
		Destroy();
		return;
	}
	TargetCharacter = Cast<ACharacter>(MyOwner);
	if (TargetCharacter)
	{
		TArray<FVector> Dash = DashSkill(); 
		MoveTargetCharacter(TargetCharacter, Dash);
	}
}


	