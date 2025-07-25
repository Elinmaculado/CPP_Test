// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "ThirdPersonCharachter.h"

#include "HealthComponent.h"
#include "WeaponTraceComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

AThirdPersonCharachter::AThirdPersonCharachter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Camera set up
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	camera->SetupAttachment(RootComponent);
	camera->bUsePawnControlRotation = true;
	swordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("swordMesh"));

	// Cuchillo
	knifeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KnifeMesh"));
	knifeMesh->SetupAttachment(GetMesh()); 
	knifeMesh->SetVisibility(false);
	if (UAnimInstance* animInstance = GetMesh()->GetAnimInstance()) {
		animInstance->OnMontageEnded.AddDynamic(this, &AThirdPersonCharachter::OnAttackEnded);
	}

	WeaponTraceComp = CreateDefaultSubobject<UWeaponTraceComponent>(TEXT("WeaponTraceComp"));

}

void AThirdPersonCharachter::BeginPlay()
{
	Super::BeginPlay();

	swordMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("swordSocket"));
	knifeMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("swordSocket"));

}

void AThirdPersonCharachter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThirdPersonCharachter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AThirdPersonCharachter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AThirdPersonCharachter::StartAttack);
	PlayerInputComponent->BindAxis("Forward", this, &AThirdPersonCharachter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AThirdPersonCharachter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AThirdPersonCharachter::LookUpCamera);
	PlayerInputComponent->BindAxis("TurnCamera", this, &AThirdPersonCharachter::TurnCamera);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &AThirdPersonCharachter::SwitchWeapon);

}

void AThirdPersonCharachter::MoveForward(float inputValue)
{
	FVector forwardDirection = GetActorForwardVector();
	AddMovementInput(forwardDirection, inputValue);
}

void AThirdPersonCharachter::MoveRight(float inputValue)
{
	FVector rightDirection = GetActorRightVector();
	AddMovementInput(rightDirection, inputValue);
}

void AThirdPersonCharachter::TurnCamera(float inputValue)
{
	AddControllerYawInput(inputValue);
}

void AThirdPersonCharachter::LookUpCamera(float inputValue)
{
	AddControllerPitchInput(inputValue);
}

void AThirdPersonCharachter::StartAttack()
{
	if (attackMontage && !isAttacking) 
	{
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		if (animInstance) {
			animInstance->Montage_Play(attackMontage);
			isAttacking = true;
			float attackDuration = attackMontage->GetPlayLength();
			GetWorldTimerManager().SetTimer(AttackResetHandle, this, &AThirdPersonCharachter::ResetAttackState, attackDuration, false);
		}
	}
}

void AThirdPersonCharachter::LineTrace()
{

	if (WeaponTraceComp && swordMesh)
	{
		UStaticMeshComponent* CurrentWeapon = bUsingSword ? swordMesh : knifeMesh;
		WeaponTraceComp->PerformWeaponTrace(CurrentWeapon, FName("Start"), FName("End"), Damage);
	}
}


void AThirdPersonCharachter::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == attackMontage) {
		isAttacking = false;
	}
}

void AThirdPersonCharachter::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

void AThirdPersonCharachter::ResetAttackState()
{
	isAttacking = false;
}

void AThirdPersonCharachter::SwitchWeapon()
{
	bUsingSword = !bUsingSword;
	swordMesh->SetVisibility(bUsingSword);
	knifeMesh->SetVisibility(!bUsingSword);
}

