// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
class UTextBlock;
class UQuestionButton;
class UButton;
class ATriviaGameMode;
struct Score
{
	int rigthAnswers;
	float time;
};
#include "TriviaMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class CPP_TEST_API UTriviaMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblTitle;
	UPROPERTY(meta = (BindWidget))
	UButton* btnPlay;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblPlay;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblHighScore;
	int highScore;
	float highTime;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblLastScore;
	int lastScore;
	float lastTime;

	void UpdateScore(int score, float time);


	FString FormatTime(float timeS);

	virtual void NativeConstruct() override;
};
