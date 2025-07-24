// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterWidget.h"
#include "Components/TextBlock.h"

void UShooterWidget::NativeConstruct()
{
	bulletsLabel->SetText(FText::FromString(""));
	reloadLabel->SetText(FText::FromString(""));
	healthLabel->SetText(FText::FromString(""));
}

void UShooterWidget::UpdateBullets(int currentBullets, int remainingBullets)
{
	FString message = FString::FromInt(currentBullets) + "/" + FString::FromInt(remainingBullets);
	bulletsLabel->SetText(FText::FromString(message));
}

void UShooterWidget::UpdateHealth(int currentHealth)
{
	FString message = "Current health: " + FString::FromInt(currentHealth);
	healthLabel->SetText(FText::FromString(message));
}

void UShooterWidget::UpadateReload(bool hasBullets)
{
	if (hasBullets) {
		reloadLabel->SetText(FText::FromString("Reload"));
	}
	else {
		reloadLabel->SetText(FText::FromString(""));
	}
}
