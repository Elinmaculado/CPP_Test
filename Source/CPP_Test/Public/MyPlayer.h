// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPlayer.generated.h"

UCLASS()
class CPP_TEST_API AMyPlayer : public AActor
{
	GENERATED_BODY()
	
public:
	AMyPlayer();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> Bullet;

	UPROPERTY(EditAnywhere)
	float shootTimer;

	UPROPERTY(EditAnywhere)
	float stopShootingTimer;

	FTimerHandle shootTimerHandleID;
	FTimerHandle stopShootingTimerHandleID;

	void Shoot();
	void StopTimer();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
