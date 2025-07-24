// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonCharachter.h"
#include "ThirdPersonPlayerAnimInstance.h"

void UThirdPersonPlayerAnimInstance::UpdateAnimationProperties(float DeltaSeconds)
{
	if (playerCharacter == nullptr) {
		playerCharacter = Cast<AThirdPersonCharachter>(TryGetPawnOwner());
	}
	if (playerCharacter) {
		FVector Velocity{ playerCharacter->GetVelocity() };
		Velocity.Z = 0;
		speed = Velocity.Size();
	}
}

void UThirdPersonPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	playerCharacter = Cast<AThirdPersonCharachter>(TryGetPawnOwner());
}
