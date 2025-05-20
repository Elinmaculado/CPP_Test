// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionObject.h"
#include "Bullet.h"

// Sets default values
ACollisionObject::ACollisionObject()
{


	//Crear el objeto de colision y nombrarlo
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionBox->SetGenerateOverlapEvents(true);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACollisionObject::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ACollisionObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACollisionObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollisionObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor && OtherActor != this) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(0, 0.5, FColor::Cyan, "Collided!!!");
		}
	}

	ABullet* bullet = Cast<ABullet>(OtherActor);
	health -= bullet->damage;
	if (health <= 0) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 0.5, FColor::Red, "Muelto!!!");
		}
	}
}

