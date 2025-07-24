// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpiralBullet.generated.h"

UCLASS()
class CPP_TEST_API ASpiralBullet : public AActor
{
	GENERATED_BODY()

public:
    ASpiralBullet();
    UPROPERTY(EditAnywhere)
    float lifetime;    
    UPROPERTY(EditAnywhere)
    float ForwardSpeed = 200.f;

    UPROPERTY(EditAnywhere)
    float Radius = 50.f;

    UPROPERTY(EditAnywhere)
    float Frequency = 1.f;

protected:

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;



    FTimerHandle lifeTimeID;
    void DestroyBullet();

private:
    float TimeAccumulator = 0.f;
    FVector StartLocation;

};
