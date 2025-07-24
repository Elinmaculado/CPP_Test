// Fill out your copyright notice in the Description page of Project Settings.


#include "WinPlatform.h"
#include "PlayerMovement.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"


// Sets default values
AWinPlatform::AWinPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionBox->SetGenerateOverlapEvents(true);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWinPlatform::OnOverlapBegin);
	
}

// Called when the game starts or when spawned
void AWinPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWinPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) {
		APlayerMovement* playerMovement = Cast<APlayerMovement>(OtherActor);
		if (playerMovement != nullptr) {
			if (IsValid(WinWidget)) {
				WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WinWidget);
				if (IsValid(WidgetInstance)) {
					WidgetInstance->AddToViewport();
					UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
				}
			}
		}
	}
}

