// Fill out your copyright notice in the Description page of Project Settings.
#include "SDaggerProjectile.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ASDaggerProjectile::ASDaggerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->UpdateCollisionProfile();
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 5000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	
}

// Called when the game starts or when spawned
void ASDaggerProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASDaggerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

