// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemConsumable.h"

// Sets default values
AItemConsumable::AItemConsumable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Item = CreateDefaultSubobject<UStaticMeshComponent>("SM_Item");
	RootComponent = SM_Item;
	SM_Item->SetSimulatePhysics(true);
	SM_Item->SetCollisionProfileName("PhysicsActor");

	SM_Highlight = CreateDefaultSubobject<UStaticMeshComponent>("SM_Highlight");
	SM_Highlight->SetupAttachment(RootComponent);
	
	Glow_Light = CreateDefaultSubobject<UPointLightComponent>("Glow_Light");
	Glow_Light->SetupAttachment(SM_Highlight);

}

// Called when the game starts or when spawned
void AItemConsumable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemConsumable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemConsumable::Interact_Implementation(APawn* InstigatorPawn)
{
	Destroy();
}


