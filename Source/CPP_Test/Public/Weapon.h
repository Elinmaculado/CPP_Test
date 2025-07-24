// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class CPP_TEST_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> Bullet;

	UPROPERTY(EditAnywhere)
	int magazineSize;
	UPROPERTY(EditAnywhere)
	int totalBullets;

	int bulletsInMagazine;

	void ReloadMagazine();

	void ShootBullet(FVector spawnLocation, FRotator spawnRotation);


	bool HasBullets();

protected:
	virtual void BeginPlay() override;
};
