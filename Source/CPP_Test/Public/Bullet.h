// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class CPP_TEST_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditAnywhere)
	float speed = 10;	
	

	UPROPERTY(EditAnywhere)
	float damage = 10;

	virtual void Tick(float DeltaTime) override;

};
