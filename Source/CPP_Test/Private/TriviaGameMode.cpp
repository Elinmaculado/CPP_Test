// Fill out your copyright notice in the Description page of Project Settings.

#include "TriviaWidget.h"
#include "TriviaMainMenu.h"
#include "TriviaPause.h"
#include "Components/Button.h"
#include "QuestionButton.h"
#include "Kismet/GameplayStatics.h"
#include "TriviaGameMode.h"

void ATriviaGameMode::BeginPlay()
{
	if (triviaWidgetClass) 
	{
		triviaWidgetInstance = CreateWidget<UTriviaWidget>(GetWorld(), triviaWidgetClass);
		if (IsValid(triviaWidgetInstance))
		{
			triviaWidgetInstance->btnPause->OnClicked.AddDynamic(this, &ATriviaGameMode::Pause);
			triviaWidgetInstance->gameMode = this;
			triviaWidgetInstance->AddToViewport();
			triviaWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (triviaPauseClass)
	{
		triviaPauseInstance = CreateWidget<UTriviaPause>(GetWorld(), triviaPauseClass);
		if (IsValid(triviaPauseInstance))
		{
			triviaPauseInstance->btnMenu->OnClicked.AddDynamic(this, &ATriviaGameMode::Menu);
			triviaPauseInstance->btnRestart->OnClicked.AddDynamic(this, &ATriviaGameMode::Restart);
			triviaPauseInstance->btnResume->OnClicked.AddDynamic(this, &ATriviaGameMode::Resume);
			triviaPauseInstance->AddToViewport();
			triviaPauseInstance->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (triviaMenuClass) 
	{
		triviaMenuInstance = CreateWidget<UTriviaMainMenu>(GetWorld(), triviaMenuClass);
		if (IsValid(triviaMenuInstance))
		{
			triviaMenuInstance->btnPlay->OnClicked.AddDynamic(this, &ATriviaGameMode::Play);
			triviaMenuInstance->AddToViewport();
		}
	}
	if (IsValid(levelMusic)) {
		UGameplayStatics::SpawnSound2D(GetWorld(), levelMusic);
	}
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}

void ATriviaGameMode::Play()
{
	if (IsValid(triviaMenuInstance) && IsValid(triviaWidgetInstance)) {
		triviaWidgetInstance->Play();
		triviaWidgetInstance->SetVisibility(ESlateVisibility::Visible);	
		triviaMenuInstance->SetVisibility(ESlateVisibility::Collapsed); 
	}
}

void ATriviaGameMode::Menu()
{
	if (IsValid(triviaMenuInstance) && IsValid(triviaWidgetInstance) && IsValid(triviaPauseInstance)) {
		triviaMenuInstance->SetVisibility(ESlateVisibility::Visible);
		triviaPauseInstance->SetVisibility(ESlateVisibility::Collapsed);
		triviaWidgetInstance->SetVisibility(ESlateVisibility::Collapsed); 
	}
}

void ATriviaGameMode::Pause()
{
	if (IsValid(triviaWidgetInstance) && IsValid(triviaPauseInstance)) {
		triviaPauseInstance->SetVisibility(ESlateVisibility::Visible); 
		triviaWidgetInstance->SetVisibility(ESlateVisibility::Collapsed); 
		
	}
}

void ATriviaGameMode::Resume()
{
	if (IsValid(triviaWidgetInstance) && IsValid(triviaPauseInstance)) {
		triviaWidgetInstance->SetVisibility(ESlateVisibility::Visible);	
		triviaPauseInstance->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ATriviaGameMode::Restart()
{
	if (IsValid(triviaWidgetInstance) && IsValid(triviaPauseInstance)) {
		triviaWidgetInstance->Play();
		triviaWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		triviaPauseInstance->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ATriviaGameMode::UpdateScore(int score, float time)
{
	if (triviaMenuInstance != nullptr) {
		triviaMenuInstance->UpdateScore(score,time);
		Menu();
	}
}
