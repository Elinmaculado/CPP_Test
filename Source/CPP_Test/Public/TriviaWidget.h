// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
class UTextBlock;
class UQuestionButton;
class UButton;
class ATriviaGameMode;

struct Answer
{
	FString text;
	bool isTrue;
};

struct Question
{
	FString question;
	Answer answer1;
	Answer answer2;
	Answer answer3;
	Answer answer4;
	Answer answer5;

	int correctAnswer;
};

#include "TriviaWidget.generated.h"
UCLASS()
class CPP_TEST_API UTriviaWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
	void ShowQuestion(Question question);
	void SetUpQuestions();
	UFUNCTION()
	void NextQuestion();


	void QuestionDelay();
	FTimerHandle questionDelayID;
	float questionDelayTime = 0.75;

	void Play();	

	UFUNCTION()
	void CheckAnswer1();
	UFUNCTION()
	void CheckAnswer2();
	UFUNCTION()
	void CheckAnswer3();
	UFUNCTION()
	void CheckAnswer4();
	UFUNCTION()
	void CheckAnswer5();


	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblQuestion;

	UPROPERTY(meta = (BindWidget))
	UQuestionButton* btnAnswer1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblAnswer1;


	UPROPERTY(meta = (BindWidget))
	UQuestionButton* btnAnswer2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblAnswer2;

	UPROPERTY(meta = (BindWidget))
	UQuestionButton* btnAnswer3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblAnswer3;

	UPROPERTY(meta = (BindWidget))
	UQuestionButton* btnAnswer4;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblAnswer4;

	UPROPERTY(meta = (BindWidget))
	UQuestionButton* btnAnswer5;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblAnswer5;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblQuestionNumbers;

	UPROPERTY(meta = (BindWidget))
	UButton* btnPause;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblPause;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblCorrect;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* lblTime;

	int currentQuestion = 0;
	int totalQuestions = 0;

	int rightAnswers = 0;
	float playTime = 0.0f;

	FString FormatTime(float time);

	TArray<Question> questions;

	ATriviaGameMode* gameMode;
};