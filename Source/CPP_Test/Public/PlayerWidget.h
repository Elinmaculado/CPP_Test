// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
class UTextBlock;
class UButton;
class AGMB;
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPP_TEST_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* scoreLabel;

	UPROPERTY(meta = (BindWidget))
	UButton* scoreButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void RaiseScore();
	void UpdateScore();

	AGMB* gameMode;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


};
