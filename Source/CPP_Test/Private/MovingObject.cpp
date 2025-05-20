// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObject.h"

// Sets default values
AMovingObject::AMovingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingObject::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(movementHandlerID, this, &AMovingObject::Move, moveTimer,true);
	GetWorldTimerManager().SetTimer(invertMovementHandlerID, this, &AMovingObject::InvertMove, moveTimer + invertMoveTimer);

}

// Called every frame
void AMovingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	rotation = FQuat(currentRotateSpeed);
	AddActorLocalRotation(rotation);
	AddActorLocalOffset(FVector(currentSpeed, 0, 0));
}

void AMovingObject::Move()
{
	Shoot();
	currentRotateSpeed = rotateSpeed;
	currentSpeed = moveSpeed;
}

void AMovingObject::InvertMove()
{
	moveSpeed *= -1;
	GetWorldTimerManager().SetTimer(deletActorHandlerID, this, &AMovingObject::DeleteActor, deleteActorTimer);

}

void AMovingObject::DeleteActor()
{
	Destroy();
}

void AMovingObject::Shoot()
{
	if (Bullet) {
		FVector spawnLocation = GetActorLocation();
		FRotator spawnRotation = GetActorRotation();
		GetWorld()->SpawnActor<AActor>(Bullet, spawnLocation, spawnRotation);

	}
}


