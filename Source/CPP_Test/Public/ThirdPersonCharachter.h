#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersonCharachter.generated.h"

UCLASS()
class CPP_TEST_API AThirdPersonCharachter : public ACharacter
{
	GENERATED_BODY()

public:
	AThirdPersonCharachter();

protected:
	virtual void BeginPlay() override;

	// Cámara
	UPROPERTY(EditAnywhere)
	class UCameraComponent* camera;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Movimiento
	void MoveForward(float inputValue);
	void MoveRight(float inputValue);
	void TurnCamera(float inputValue);
	void LookUpCamera(float inputValue);

	// Combate
	void StartAttack();
	UFUNCTION(BlueprintCallable)
	void LineTrace();
	void ResetAttackState();

	// Armas
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* swordMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* knifeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimMontage* attackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimMontage* switchWeaponMontage;

	UPROPERTY(BlueprintReadWrite)
	bool isAttacking = false;

	UPROPERTY(EditAnywhere)
	int Damage;

	FTimerHandle AttackResetHandle;

	// Alternar arma
	void SwitchWeapon();
	void PlaySwitchWeaponAnimation();
	UPROPERTY(EditAnywhere, Category="Combat")
	bool bUsingSword = true; // true = espada, false = cuchillo
	bool bIsSwitchingWeapon = false;

	// Callback para todos los montages
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	class UAIPerceptionStimuliSourceComponent* StimulusSource;
	void SetupStimulusSource();

	// Componente para el trace
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class UWeaponTraceComponent* WeaponTraceComp;
};
