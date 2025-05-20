// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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

	UPROPERTY(EditAnywhere)
	float moveVelocity;

	UPROPERTY(EditAnywhere)
	float rotationVelocity;
};
