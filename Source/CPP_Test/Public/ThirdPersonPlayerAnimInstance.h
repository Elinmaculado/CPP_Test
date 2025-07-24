// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
class AThirdPersonCharachter;
#include "ThirdPersonPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPP_TEST_API UThirdPersonPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaSeconds);
	virtual void NativeInitializeAnimation() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowAbstract = "true"))
	AThirdPersonCharachter* playerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowAbstract = "true"))
	float speed;
	
};
