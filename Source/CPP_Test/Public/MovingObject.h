// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObject.generated.h"
/*
Ejercicio
Hacer que el objeto avance, rote y dispare en la 1era corrutina
En la segunda corrutina vamos a hacer que el objeto vaya hacia atrás, siga rotando y dispare
En la tercera corrutina hacer desaparecer el objeto
crear variables editables para la velocidad de avanzar, velocidad de rotación y 
variables editables para los timers
*/

UCLASS()
class CPP_TEST_API AMovingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTimerHandle movementHandlerID;
	FTimerHandle invertMovementHandlerID;
	FTimerHandle deletActorHandlerID;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> Bullet;


	UPROPERTY(EditAnywhere)
	float moveSpeed;
	float currentSpeed;

	UPROPERTY(EditAnywhere)
	FRotator rotateSpeed;
	FRotator currentRotateSpeed;
	FQuat rotation;

	UPROPERTY(EditAnywhere)
	float moveTimer;
	UPROPERTY(EditAnywhere)
	float invertMoveTimer;
	UPROPERTY(EditAnywhere)
	float deleteActorTimer;

	void Move();
	void InvertMove();
	void DeleteActor();
	void Shoot();
};
