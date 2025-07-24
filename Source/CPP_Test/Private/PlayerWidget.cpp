// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GMB.h"

void UPlayerWidget::NativeConstruct()
{
	if (!gameMode) {
		UE_LOG(LogTemp, Warning, TEXT("Game mode is NULL"));
	}
	if (!scoreLabel) {
		UE_LOG(LogTemp, Warning, TEXT("Score label is NULL"));
	}

	FString scoreString = FString::FromInt(gameMode->score);

	if (scoreButton) {
		scoreButton->OnClicked.AddDynamic(this, &UPlayerWidget::RaiseScore);
	}
}

void UPlayerWidget::UpdateScore()
{
	FString scoreString = FString::FromInt(gameMode->score);
	scoreLabel->SetText(FText::FromString(scoreString));
}

void UPlayerWidget::RaiseScore()
{

	if (gameMode) {
		
		gameMode->score += 10;
		UpdateScore();
	}
}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!gameMode) {
		UE_LOG(LogTemp, Warning, TEXT("Game mode is NULL"));
	}
}
