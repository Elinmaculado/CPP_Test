// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerMovement.h"

APlayerMovement::APlayerMovement()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerMovement::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Vertical", this, &APlayerMovement::VerticalAxis);
	InputComponent->BindAxis("Horizontal", this, &APlayerMovement::HorizontalAxis);
}

void APlayerMovement::VerticalAxis(float value)
{
	float deltaTime = GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(FVector(value * moveVelocity * deltaTime, 0, 0));
}

void APlayerMovement::HorizontalAxis(float value)
{
	float deltaTime = GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(FRotator(0,value * rotationVelocity * deltaTime,0));
}

