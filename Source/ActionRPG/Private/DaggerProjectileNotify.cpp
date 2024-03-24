// Fill out your copyright notice in the Description page of Project Settings.


#include "DaggerProjectileNotify.h"

#include "SCharacter.h"
#include "Engine.h"

void UDaggerProjectileNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if(MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ASCharacter* Player = Cast<ASCharacter>(MeshComp->GetOwner());

		if(Player != NULL)
		{
			Player->SpawnProjectileAttack();
		} 
		
	}
}
