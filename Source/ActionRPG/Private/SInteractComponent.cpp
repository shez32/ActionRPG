// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractComponent.h"

#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractComponent::USInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	
	MyOwner = GetOwner();
	// ...
	
}


// Called every frame
void USInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractComponent::Interact()
{
	
	TArray<FOverlapResult> HitResults;
	
	FVector StartPosition = MyOwner->GetActorLocation();
	FQuat Rotation = FQuat::Identity; 

	FCollisionObjectQueryParams ObjQueryParams;
	ObjQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	float SphereRadius = 130.0f;
	
	FCollisionShape OverlapShape;
	OverlapShape.SetSphere(SphereRadius);

	FCollisionQueryParams ColQueryParams;
	ColQueryParams.AddIgnoredActor(MyOwner);
	
	bool blockingHit = GetWorld()->OverlapMultiByObjectType(HitResults, StartPosition, Rotation, ObjQueryParams, OverlapShape, ColQueryParams);

	FColor LineColor = blockingHit ? FColor::Green : FColor::Red;

	for(FOverlapResult Result: HitResults)
	{
		AActor* HitActor = Result.GetActor();

		if(HitActor)
		{
			if(HitActor->Implements<USGameplayInterface>() && isActorInSight(HitActor))
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
			}
		}

		DrawDebugSphere(GetWorld(), MyOwner->GetActorLocation(), SphereRadius, 32, LineColor, false, 5.0f);
	}
}

bool USInteractComponent::isActorInSight(AActor* actorInQuestion)
{
	APawn* MyPawn = Cast<APawn>(MyOwner);
	
	float result =	FVector::DotProduct(MyPawn->GetControlRotation().Vector(), actorInQuestion->GetActorForwardVector());

	//FString outputStr = FString::SanitizeFloat(result);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::White, *outputStr);

	if(FMath::IsNearlyEqual(result, 1.0, 0.35))
	{
		return true;
	}
	else
	{
		return false;
	}
}



