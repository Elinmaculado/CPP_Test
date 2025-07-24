// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiralBullet.h"

// Sets default values
ASpiralBullet::ASpiralBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpiralBullet::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
    GetWorldTimerManager().SetTimer(lifeTimeID, this, &ASpiralBullet::DestroyBullet, lifetime);
}

// Called every frame
void ASpiralBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    TimeAccumulator += DeltaTime;

    FVector Forward = GetActorForwardVector() * ForwardSpeed * TimeAccumulator;

    float Angle = TimeAccumulator * Frequency * 2.f * PI;
    FVector CircularOffset =
        GetActorRightVector() * Radius * FMath::Cos(Angle) +
        GetActorUpVector() * Radius * FMath::Sin(Angle);

    FVector NewLocation = StartLocation + Forward + CircularOffset;

    SetActorLocation(NewLocation);
}



void ASpiralBullet::DestroyBullet() {
    Destroy();
}

