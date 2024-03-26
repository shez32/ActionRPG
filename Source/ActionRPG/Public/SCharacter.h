// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONRPG_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	FName ProjectileSpawnSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimMontages")
	UAnimMontage* DaggerThrowMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimMontages")
	UAnimMontage* DaggerThrowReadyMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimMontages")
	UAnimMontage* DaggerThrowCancelMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float ZoomAmount = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float MinCameraDistance = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float MaxCameraDistance = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float ZoomSpeed = 5.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float AlphaADS = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dagger")
	FTransform AimTransform;
	
public:
	// Sets default values for this character's properties
	ASCharacter();

	void SpawnProjectileAttack();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isAiming = false;

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComp;
	
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);
	
	void PrimaryAttack();
	
	void AimDownSightPressed();
	void AimDownSightReleased();

	void JumpCharacter();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
