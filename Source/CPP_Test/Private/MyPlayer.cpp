// Fill out your copyright notice in the Description page of Project Settings.
#include "MyPlayer.h"

AMyPlayer::AMyPlayer() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMyPlayer::Shoot()
{
	if (Bullet) {
		FVector spawnLocation = GetActorLocation();
		FRotator spawnRotation = GetActorRotation();
		GetWorld()->SpawnActor<AActor>(Bullet,spawnLocation,spawnRotation);	
	}
}

void AMyPlayer::StopTimer()
{
	GetWorldTimerManager().ClearTimer(shootTimerHandleID);
}



void AMyPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	//ID,where to execute, what to execute,timer,inLoop
	GetWorldTimerManager().SetTimer(shootTimerHandleID, this, &AMyPlayer::Shoot, shootTimer,true);
	GetWorldTimerManager().SetTimer(stopShootingTimerHandleID, this, &AMyPlayer::StopTimer, stopShootingTimer);
}
