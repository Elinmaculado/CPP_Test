#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CollisionObject.generated.h"


UCLASS()
class CPP_TEST_API ACollisionObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollisionObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult &SweepResult);

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;
	UPROPERTY(EditAnywhere)
	float health = 100;
};
