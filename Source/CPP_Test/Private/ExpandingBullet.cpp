// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpandingBullet.h"

// Sets default values
AExpandingBullet::AExpandingBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExpandingBullet::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(lifeTimeID, this, &AExpandingBullet::DestroyBullet, lifetime);
}

// Called every frame
void AExpandingBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector currentScale = GetActorScale3D();
	FVector newScale = currentScale + (FVector::OneVector * growRate * DeltaTime);
	SetActorScale3D(newScale);
	AddActorLocalOffset(FVector(speed, 0, 0));
}

void AExpandingBullet::DestroyBullet() {
	Destroy();
}

