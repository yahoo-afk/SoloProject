// Fill out your copyright notice in the Description page of Project Settings.


#include "SorwdWave.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "NiagaraComponent.h"

// 필요하면 스킬이 엑터를 호출한다
// Sets default values
ASwordWave::ASwordWave()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComp= CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetBoxExtent(FVector(100.f, 100.0f, 20.0f) );
	//??
	CollisionComp->SetCollisionProfileName(TEXT("Projectile"));
	RootComponent = CollisionComp;
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->MaxSpeed = 2000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	NiagaraComponent->SetupAttachment(CollisionComp);
	
	InitialLifeSpan = 2.f;
	Damage = 10.f;
	
	UE_LOG(LogTemp, Error, TEXT("Sword Wave"));
	if (CollisionComp)
	{
		CollisionComp->OnComponentHit.AddDynamic(this, &ASwordWave::OnHit);
	}
	
}

void ASwordWave::BeginPlay()
{
	Super::BeginPlay();
	if (NiagaraComponent && NiagaraSystem)
	{
		NiagaraComponent->SetAsset(NiagaraSystem);
		NiagaraComponent->Activate();
	}
	
}
void ASwordWave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASwordWave::OnHit(UPrimitiveComponent* HitComp,
                       AActor* OtherActor, 
                       UPrimitiveComponent* OtherComp, 
                       FVector NormalImpulse, 
                       const FHitResult& Hit)
{
	if (OtherActor&& OtherActor != OwnerActor)
	{
		UGameplayStatics::ApplyDamage(OtherActor
			,Damage,
			nullptr,
			this,
			nullptr);
	}
}


