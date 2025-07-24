// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bCabTakeDamage = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::Die()
{
	GetOwner()->Destroy();
}

void UHealthComponent::TakeDamage(float damage)
{
	//health -= damage;
	if (bCabTakeDamage)
	{
		health -= damage;
		bCabTakeDamage = false;
		FTimerHandle invincibilityTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(invincibilityTimerHandle, this, &UHealthComponent::AllowTakeDamage, 0.5f, false);
	}
	if (health <= 0)
		Die();
}

void UHealthComponent::AllowTakeDamage()
{
	bCabTakeDamage = true;
}

