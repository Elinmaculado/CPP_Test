// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TriviaMainMenu.h"


void UTriviaMainMenu::UpdateScore(int score, float time)
{
	lastScore = score;
	lastTime = time;
	lblLastScore->SetText(FText::FromString("Last score: " + FString::FromInt(score) + " " + FormatTime(time)));

	if (score < highScore) { return; }
	if (score == highScore) {
		if (time > highTime) {
			return;
		}
	}
	highScore = score;
	highTime = time;
	lblHighScore->SetText(FText::FromString("High score: " + FString::FromInt(highScore) + " " + FormatTime(highTime)));
}

void UTriviaMainMenu::NativeConstruct()
{
	lblTitle->SetText(FText::FromString("Trivia Game"));
	lblPlay->SetText(FText::FromString("Play"));
	lblHighScore->SetText(FText::FromString("High score: - --:--"));
	lblLastScore->SetText(FText::FromString("Last score: - --:--"));
}

FString UTriviaMainMenu::FormatTime(float timeS)
{
	int32 totalTime = FMath::RoundToInt32(timeS);
	int32 minutes = totalTime / 60;
	int32 seconds = totalTime % 60;

	return FString::Printf(TEXT("%02d:%02d"),minutes,seconds);
}



