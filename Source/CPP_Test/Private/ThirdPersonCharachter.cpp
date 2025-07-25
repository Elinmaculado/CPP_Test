#include "Camera/CameraComponent.h"
#include "ThirdPersonCharachter.h"
#include "WeaponTraceComponent.h"
#include "HealthComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "TimerManager.h"

AThirdPersonCharachter::AThirdPersonCharachter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Cámara
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	camera->SetupAttachment(RootComponent);
	camera->bUsePawnControlRotation = true;

	// Armas
	swordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordMesh"));
	knifeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KnifeMesh"));
	knifeMesh->SetupAttachment(GetMesh()); 
	knifeMesh->SetVisibility(false); // empieza invisible

	// Componente de trace
	WeaponTraceComp = CreateDefaultSubobject<UWeaponTraceComponent>(TEXT("WeaponTraceComp"));
}

void AThirdPersonCharachter::BeginPlay()
{
	Super::BeginPlay();

	// Montar ambas armas en el mismo socket
	swordMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("swordSocket"));
	knifeMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("swordSocket"));

	// Bind de los montages
	if (UAnimInstance* animInstance = GetMesh()->GetAnimInstance()) {
		animInstance->OnMontageEnded.AddDynamic(this, &AThirdPersonCharachter::OnMontageEnded);
	}
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
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &AThirdPersonCharachter::SwitchWeapon);
	PlayerInputComponent->BindAxis("Forward", this, &AThirdPersonCharachter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AThirdPersonCharachter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AThirdPersonCharachter::LookUpCamera);
	PlayerInputComponent->BindAxis("TurnCamera", this, &AThirdPersonCharachter::TurnCamera);
}

void AThirdPersonCharachter::MoveForward(float inputValue)
{
	AddMovementInput(GetActorForwardVector(), inputValue);
}

void AThirdPersonCharachter::MoveRight(float inputValue)
{
	AddMovementInput(GetActorRightVector(), inputValue);
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
	if (attackMontage && !isAttacking && !bIsSwitchingWeapon) 
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
	if (WeaponTraceComp)
	{
		UStaticMeshComponent* CurrentWeapon = bUsingSword ? swordMesh : knifeMesh;
		WeaponTraceComp->PerformWeaponTrace(CurrentWeapon, FName("Start"), FName("End"), Damage);
	}
}

void AThirdPersonCharachter::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(UAISense_Sight::StaticClass());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

void AThirdPersonCharachter::ResetAttackState()
{
	isAttacking = false;
}

void AThirdPersonCharachter::SwitchWeapon()
{
	if (bIsSwitchingWeapon || isAttacking) return;
	PlaySwitchWeaponAnimation();
}

void AThirdPersonCharachter::PlaySwitchWeaponAnimation()
{
	if (switchWeaponMontage && !bIsSwitchingWeapon && !isAttacking)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			bIsSwitchingWeapon = true;
			AnimInstance->Montage_Play(switchWeaponMontage);
		}
	}
}

void AThirdPersonCharachter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == attackMontage)
	{
		isAttacking = false;
	}
	else if (Montage == switchWeaponMontage)
	{
		// Aquí hacemos el cambio real de arma al terminar la animación
		bUsingSword = !bUsingSword;
		swordMesh->SetVisibility(bUsingSword);
		knifeMesh->SetVisibility(!bUsingSword);
		bIsSwitchingWeapon = false;
	}
}
