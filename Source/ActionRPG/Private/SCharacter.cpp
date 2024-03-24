// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/Internal/Kismet/BlueprintTypeConversions.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetRelativeLocation(FVector(0,0,50));
	SpringArmComp->SocketOffset = FVector(0, 50, 0);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	bUseControllerRotationYaw = false; 
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpringArmComp->TargetArmLength = MaxCameraDistance;
}

void ASCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(),value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, value);
}

void ASCharacter::JumpCharacter()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, "JumpCalled");

	Jump();
}


void ASCharacter::PrimaryAttack()
{
	if(isAiming)
	{
		PlayAnimMontage(DaggerThrowMontage, 1, NAME_None);
	}
}

void ASCharacter::AimDownSightPressed()
{
	isAiming = true;
	PlayAnimMontage(DaggerThrowReadyMontage, 1, NAME_None);
}

void ASCharacter::AimDownSightReleased()
{
	isAiming = false;
	PlayAnimMontage(DaggerThrowCancelMontage, 1, NAME_None);
}

void ASCharacter::SpawnProjectileAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation(ProjectileSpawnSocket);
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float InterpZoomSpeed = ZoomSpeed * DeltaTime;

	if(isAiming)
	{
		AlphaADS = FMath::Clamp(AlphaADS + InterpZoomSpeed, 0.0f, 1.0f);
	}
	else
	{
		AlphaADS = FMath::Clamp(AlphaADS - InterpZoomSpeed, 0.0f, 1.0f);
	}

	SpringArmComp->TargetArmLength = FMath::Lerp(MaxCameraDistance, MinCameraDistance, AlphaADS);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnInput", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::JumpCharacter);

	PlayerInputComponent->BindAction("DaggerThrow", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ASCharacter::AimDownSightPressed);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ASCharacter::AimDownSightReleased);
	
}

