// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExpandingBullet.generated.h"

UCLASS()
class CPP_TEST_API AExpandingBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExpandingBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle lifeTimeID;
	void DestroyBullet();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float lifetime;
	UPROPERTY(EditAnywhere)
	float growRate;
	UPROPERTY(EditAnywhere)
	float speed = 10;

};
