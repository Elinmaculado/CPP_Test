
#include "WeaponTraceComponent.h"
#include "DrawDebugHelpers.h"
#include "HealthComponent.h"
#include "GameFramework/Actor.h"

UWeaponTraceComponent::UWeaponTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UWeaponTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponTraceComponent::PerformWeaponTrace(UStaticMeshComponent* WeaponMesh, FName StartSocket, FName EndSocket, int Damage)
{
	if (!WeaponMesh) return;

	FVector StartLocation = WeaponMesh->GetSocketLocation(StartSocket);
	FVector EndLocation = WeaponMesh->GetSocketLocation(EndSocket);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams);

	if (bDrawDebug)
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1.0f, 0, 1.0f);
	}

	if (HitResult.bBlockingHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (IsValid(HitActor))
		{
			UHealthComponent* HealthComp = HitActor->FindComponentByClass<UHealthComponent>();
			if (HealthComp)
			{
				HealthComp->TakeDamage(Damage);
			}
		}
	}
}