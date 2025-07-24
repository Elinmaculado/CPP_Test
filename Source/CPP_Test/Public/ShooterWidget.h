// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
class UTextBlock;
#include "ShooterWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPP_TEST_API UShooterWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock* bulletsLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* reloadLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* healthLabel;

	virtual void NativeConstruct() override;

public:
	void UpdateBullets(int currentBullets, int remainingBullets);
	void UpdateHealth(int currentHealt);
	void UpadateReload(bool needReload);
};
