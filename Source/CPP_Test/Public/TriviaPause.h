// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
class UButton;
#include "Blueprint/UserWidget.h"
#include "TriviaPause.generated.h"

/**
 * 
 */
UCLASS()
class CPP_TEST_API UTriviaPause : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* btnMenu;
	UPROPERTY(meta = (BindWidget))
	UButton* btnResume;
	UPROPERTY(meta = (BindWidget))
	UButton* btnRestart;
};
