// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructableActor.h"

#include "SCharacter.h"

// Sets default values
ADestructableActor::ADestructableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DestructibleSM = CreateDefaultSubobject<UStaticMeshComponent>("DestructibleSM");
	DestructibleSM->SetupAttachment(RootComponent);
	DestructibleSM->SetSimulatePhysics(true);
	DestructibleSM->SetCollisionProfileName("PhysicsActor");
	DestructibleSM->OnComponentHit.AddDynamic(this, &ADestructableActor::OnActorHit);
	
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(DestructibleSM);
	RadialForceComp->Radius = 600.0f;
	RadialForceComp->ImpulseStrength = 1000.0f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void ADestructableActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADestructableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructableActor::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 22.0f, FColor::White, OtherActor->GetName());

	if(OtherActor->GetName() != "Floor")
	{
		RadialForceComp->FireImpulse();
	}
}




