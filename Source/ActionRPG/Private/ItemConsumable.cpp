// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemConsumable.h"

#include "SCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

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

	SphereCol = CreateDefaultSubobject<USphereComponent>("SphereCol");
	SphereCol->SetupAttachment(RootComponent);
	SphereCol->InitSphereRadius(7.0f);
	SphereCol->OnComponentBeginOverlap.AddDynamic(this, &AItemConsumable::AItemConsumable::OnActorOverlap);
	
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
	//FTimerHandle UnusedHandle;
	
	SM_Item->SetSimulatePhysics(false);
	SM_Item->SetCollisionProfileName("NoCollision");

	FLatentActionInfo defaultLatentInfo;
	defaultLatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo(SM_Item, InstigatorPawn->GetActorLocation(), FRotator::ZeroRotator,
		true, false, 0.7f, false, EMoveComponentAction::Type::Move , defaultLatentInfo);

	//GetWorldTimerManager().SetTimer(UnusedHandle, this, &AItemConsumable::DestroyItem, 0.7f, false, -1.0f);

}

void AItemConsumable::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool Sweep, const FHitResult& Hit)
{
	ASCharacter* Player = Cast<ASCharacter>(OtherActor);

	if(Player)
	{
		DestroyItem();
	}
}


void AItemConsumable::DestroyItem()
{
	Destroy();
}


