// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerMovement.h"
#include "PlayerWidget.h"
#include "GMB.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "ShooterWidget.h"



APlayerMovement::APlayerMovement()
{
	PrimaryActorTick.bCanEverTick = true;

	Weapon1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon1"));
	Weapon1->SetupAttachment(RootComponent);

	Weapon2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon2"));
	Weapon2->SetupAttachment(RootComponent);

	Weapon3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon3"));
	Weapon3->SetupAttachment(RootComponent);
}

void APlayerMovement::BeginPlay()
{
	Super::BeginPlay();
	if (Weapon1) 
	{
		Weapon1->SetChildActorClass(Weapon1Class);
	}
	if (Weapon2)
	{
		Weapon2->SetChildActorClass(Weapon2Class);
	}
	if (Weapon3)
	{
		Weapon3->SetChildActorClass(Weapon3Class);
	}

	SetWeapon1();

	/*
	if (playerUIClass && GetController()->IsLocalPlayerController()) {
		UPlayerWidget* ui = CreateWidget<UPlayerWidget>(GetWorld(), playerUIClass);
		if (ui != nullptr) {
			AGMB* gameMode = Cast<AGMB>(GetWorld()->GetAuthGameMode());
			ui->gameMode = gameMode;
			ui->UpdateScore();
			ui->AddToViewport();
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		}
	}
	*/

	if (playerShooterUIClass && GetController()->IsLocalPlayerController()) {
		if (IsValid(playerShooterUIClass)) {
			playerShooterUIInstance = CreateWidget<UShooterWidget>(GetWorld(), playerShooterUIClass);
			if (IsValid(playerShooterUIInstance)) {
				playerShooterUIInstance->AddToViewport();
				UpdateBulletsUI();
				playerShooterUIInstance->UpdateHealth(health);
				
				UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
			}
		}
	}
}

void APlayerMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Vertical", this, &APlayerMovement::VerticalAxis);
	InputComponent->BindAxis("Horizontal", this, &APlayerMovement::HorizontalAxis);
	InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &APlayerMovement::Shoot);
	InputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &APlayerMovement::ReloadWeapon);
	InputComponent->BindAction("Weapon1", EInputEvent::IE_Pressed, this, &APlayerMovement::SetWeapon1);
	InputComponent->BindAction("Weapon2", EInputEvent::IE_Pressed, this, &APlayerMovement::SetWeapon2);
	InputComponent->BindAction("Weapon3", EInputEvent::IE_Pressed, this, &APlayerMovement::SetWeapon3);
}

void APlayerMovement::VerticalAxis(float value)
{
	float deltaTime = GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(FVector(value * moveVelocity * deltaTime, 0, 0));
}

void APlayerMovement::HorizontalAxis(float value)
{
	float deltaTime = GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(FRotator(0,value * rotationVelocity * deltaTime,0));
}

void APlayerMovement::Shoot()
{
	FVector spawnLocation = GetActorLocation();
	FRotator spawnRotation = GetActorRotation();
	CurrentWeapon->ShootBullet(spawnLocation,spawnRotation);
	UpdateBulletsUI();
}

void APlayerMovement::ReloadWeapon()
{
	CurrentWeapon->ReloadMagazine();
	UpdateBulletsUI();
}

void APlayerMovement::SetWeapon1()
{
	CurrentWeapon = Cast<AWeapon>(Weapon1->GetChildActor());
	UpdateBulletsUI();
}

void APlayerMovement::SetWeapon2()
{
	CurrentWeapon = Cast<AWeapon>(Weapon2->GetChildActor());
	UpdateBulletsUI();
}

void APlayerMovement::SetWeapon3()
{
	CurrentWeapon = Cast<AWeapon>(Weapon3->GetChildActor());
	UpdateBulletsUI();
}

void APlayerMovement::UpdateBulletsUI()
{
	if (IsValid(playerShooterUIInstance)) {
		playerShooterUIInstance->UpdateBullets(CurrentWeapon->bulletsInMagazine, CurrentWeapon->totalBullets);
		playerShooterUIInstance->UpadateReload(CurrentWeapon->HasBullets());
	}
}

void APlayerMovement::DealDamage(float damage)
{
	health -= damage;
	if (IsValid(playerShooterUIInstance)) {
		playerShooterUIInstance->UpdateHealth(health);
	}
	if (GEngine) {
		FString message = FString::SanitizeFloat(health);
		GEngine->AddOnScreenDebugMessage(0, 0.5, FColor::Red,message);
		
		if (health <= 0) {
			GEngine->AddOnScreenDebugMessage(1, 0.5, FColor::Red, "Muelto!!!");
			Destroy();
		}
	}	
}



