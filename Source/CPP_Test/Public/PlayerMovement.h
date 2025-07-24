// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Damagable.h"
class AWeapon;
class UPlayerWidget;
class UShooterWidget;
#include "PlayerMovement.generated.h"

UCLASS()
class CPP_TEST_API APlayerMovement : public APawn
{
	GENERATED_BODY()

public:
	APlayerMovement();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void VerticalAxis(float value);
	void HorizontalAxis(float value);
	void Shoot();
	void ReloadWeapon();

	UPROPERTY(EditAnywhere)
	float moveVelocity;

	UPROPERTY(EditAnywhere)
	float rotationVelocity;


	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> Weapon1Class;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> Weapon2Class;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> Weapon3Class;

	class UChildActorComponent* Weapon1;
	class UChildActorComponent* Weapon2;
	class UChildActorComponent* Weapon3;

	void SetWeapon1();
	void SetWeapon2();
	void SetWeapon3();

	void UpdateBulletsUI();

	UPROPERTY(EditAnywhere)
	float health;
	void DealDamage(float damage);

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPlayerWidget> playerUIClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UShooterWidget> playerShooterUIClass;

private:
	AWeapon* CurrentWeapon;
	UShooterWidget* playerShooterUIInstance;
};
