// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AWeapon::BeginPlay() 
{
	ReloadMagazine();
}

void AWeapon::ReloadMagazine()
{
	if (totalBullets <= 0) 
	{ return; }

	int neededBullet = magazineSize - bulletsInMagazine;

	if (neededBullet <= 0) {  return; }

	int bulletsToReload = neededBullet < totalBullets ? neededBullet : totalBullets;

	totalBullets -= bulletsToReload;

	bulletsInMagazine += bulletsToReload;
}

void AWeapon::ShootBullet(FVector spawnLocation, FRotator spawnRotation)
{
	if (Bullet && bulletsInMagazine>0) {
		bulletsInMagazine--;
		GetWorld()->SpawnActor<AActor>(Bullet, spawnLocation, spawnRotation);
	}
}


bool AWeapon::HasBullets()
{
	return bulletsInMagazine<=0 && totalBullets > 0;
}

