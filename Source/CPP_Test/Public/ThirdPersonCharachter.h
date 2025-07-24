// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
class UAnimMontage;
#include "ThirdPersonCharachter.generated.h"

UCLASS()
class CPP_TEST_API AThirdPersonCharachter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersonCharachter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* camera;


public:	
	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float inputValue);
	void MoveRight(float inputValue);
	void TurnCamera(float inputValue);
	void LookUpCamera(float inputValue);
	void StartAttack();
	UFUNCTION(BlueprintCallable)
	void LineTrace();



	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* swordMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* attackMontage;
	UPROPERTY(BlueprintReadWrite)
	bool isAttacking = false;
	void OnAttackEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditAnywhere)
	int Damage;

	FTimerHandle AttackResetHandle;

	void ResetAttackState();
};
