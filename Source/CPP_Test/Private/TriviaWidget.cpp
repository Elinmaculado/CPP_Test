// Fill out your cop;yright notice in the Description page of Project Settings.

#include "QuestionButton.h"
#include "Components/TextBlock.h"
#include "TriviaMainMenu.h"
#include "TriviaGameMode.h"
#include "TriviaWidget.h"


void UTriviaWidget::NativeConstruct()
{
	btnAnswer1->OnClicked.AddDynamic(this, &UTriviaWidget::CheckAnswer1);
	btnAnswer2->OnClicked.AddDynamic(this, &UTriviaWidget::CheckAnswer2);
	btnAnswer3->OnClicked.AddDynamic(this, &UTriviaWidget::CheckAnswer3);
	btnAnswer4->OnClicked.AddDynamic(this, &UTriviaWidget::CheckAnswer4);
	btnAnswer5->OnClicked.AddDynamic(this, &UTriviaWidget::CheckAnswer5);

	UpdateCanTick();
}

void UTriviaWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
		playTime += GetWorld()->GetDeltaSeconds();
		lblTime->SetText(FText::FromString(FormatTime(playTime)));
}


void UTriviaWidget::SetUpQuestions()
{
	//Question 1
	Question q1;
	q1.question = "¿A que tipo de daño es debil Caligo, el miasma de la noche?";

	q1.answer1.text = "Rayo";
	q1.answer1.isTrue = false;

	q1.answer2.text = "Sagrado";
	q1.answer2.isTrue = false;

	q1.answer3.text = "Magico";
	q1.answer3.isTrue = false;

	q1.answer4.text = "Fuego";
	q1.answer4.isTrue = true;

	q1.answer5.text = "Madness";
	q1.answer5.isTrue = false;
	questions.Add(q1);

	//Question 2
	Question q2;
	q2.question = "¿Con que señor de la noche puedes hacer un trato antes de iniciar el combate?";

	q2.answer1.text = "Libra, creatura de la noche ";
	q2.answer1.isTrue = true;

	q2.answer2.text = "Adel, baron de la noche";
	q2.answer2.isTrue = false;

	q2.answer3.text = "Gnoster, sabiduria de la noche";
	q2.answer3.isTrue = false;

	q2.answer4.text = "Gladius, bestia de la noche";
	q2.answer4.isTrue = false;

	q2.answer5.text = "Maris, profundidad de la noche";
	q2.answer5.isTrue = false;
	questions.Add(q2);


	//Question 3
	Question q3;
	q3.question = "¿Que personaje tiene una skin que referencia al Caballero del sol Solaire?";

	q3.answer1.text = "Rider";
	q3.answer1.isTrue = false;

	q3.answer2.text = "Wielder";
	q3.answer2.isTrue = false;

	q3.answer3.text = "Guardian";
	q3.answer3.isTrue = true;

	q3.answer4.text = "Revenant";
	q3.answer4.isTrue = false;

	q3.answer5.text = "Recluse";
	q3.answer5.isTrue = false;
	
	questions.Add(q3);

	//Question 4
	Question q4;
	q4.question = "¿Cual de los siguientes no es un jefe con el que se pueda luchar en el juego?";

	q4.answer1.text = "Dragon boquiabierto";
	q4.answer1.isTrue = false;

	q4.answer2.text = "Freja, la amada del duque";
	q4.answer2.isTrue = false;

	q4.answer3.text = "Rey sin nombre";
	q4.answer3.isTrue = false;

	q4.answer4.text = "Caballeria noctura";
	q4.answer4.isTrue = false;

	q4.answer5.text = "Campeon Gundyr";
	q4.answer5.isTrue = true;
	
	questions.Add(q4);


	//Question 5 
	Question q5;
	q5.question = "¿Cual es el nombre de la moneda que se obtiene a completar una expedicion?";

	q5.answer1.text = "Almas";
	q5.answer1.isTrue = false;

	q5.answer2.text = "Pesetas";
	q5.answer2.isTrue = false;

	q5.answer3.text = "Chelines";
	q5.answer3.isTrue = false;

	q5.answer4.text = "Oscuridad";
	q5.answer4.isTrue = true;

	q5.answer5.text = "Runas";
	q5.answer5.isTrue = false;

	questions.Add(q5);

	totalQuestions = questions.Num();
	FString total = FString::FromInt(currentQuestion) + "/" + FString::FromInt(totalQuestions);
	lblQuestionNumbers->SetText(FText::FromString(total));
	lblCorrect->SetText(FText::FromString(FString::FromInt(rightAnswers)));

}
void UTriviaWidget::NextQuestion()
{
	if (questions.IsEmpty()) {
		if (gameMode != nullptr) {
			gameMode->UpdateScore(rightAnswers, playTime);
		}
		return;
	}
	int next = FMath::RandRange(0, questions.Num() - 1);
	
	currentQuestion++;

	btnAnswer1->SetVisibility(ESlateVisibility::Visible);
	btnAnswer2->SetVisibility(ESlateVisibility::Visible);
	btnAnswer3->SetVisibility(ESlateVisibility::Visible);
	btnAnswer4->SetVisibility(ESlateVisibility::Visible);
	btnAnswer5->SetVisibility(ESlateVisibility::Visible);

	FString total = FString::FromInt(currentQuestion) + "/" + FString::FromInt(totalQuestions);
	lblQuestionNumbers->SetText(FText::FromString(total));
	ShowQuestion(questions[next]);
	questions.RemoveAt(next);
	lblCorrect->SetText(FText::FromString(FString::FromInt(rightAnswers)));
}
void UTriviaWidget::QuestionDelay()
{
	btnAnswer1->SetVisibility(ESlateVisibility::HitTestInvisible);
	btnAnswer2->SetVisibility(ESlateVisibility::HitTestInvisible);
	btnAnswer3->SetVisibility(ESlateVisibility::HitTestInvisible);
	btnAnswer4->SetVisibility(ESlateVisibility::HitTestInvisible);
	btnAnswer5->SetVisibility(ESlateVisibility::HitTestInvisible);

	GetWorld()->GetTimerManager().SetTimer(questionDelayID, this, &UTriviaWidget::NextQuestion, questionDelayTime,false);
}
void UTriviaWidget::Play()
{
	questions.Empty();
	totalQuestions = 0;
	currentQuestion = 0;
	rightAnswers = 0;
	playTime = 0;
	SetUpQuestions();
	NextQuestion();
}
void UTriviaWidget::CheckAnswer1()
{
	if (btnAnswer1->isRight) {
		rightAnswers++;
		btnAnswer1->SetBackgroundColor(FLinearColor(0, 1, 0, 1));
	}
	else {
		btnAnswer1->SetBackgroundColor(FLinearColor(1, 0, 0, 1));
	}
	QuestionDelay();
}
void UTriviaWidget::CheckAnswer2()
{
	if (btnAnswer2->isRight) {
		rightAnswers++;
		btnAnswer2->SetBackgroundColor(FLinearColor(0, 1, 0, 1));
	}
	else {
		btnAnswer2->SetBackgroundColor(FLinearColor(1, 0, 0, 1));
	} 
	QuestionDelay();
}
void UTriviaWidget::CheckAnswer3()
{
	if (btnAnswer3->isRight) {
		rightAnswers++;
		btnAnswer3->SetBackgroundColor(FLinearColor(0, 1, 0, 1));
	}
	else {
		btnAnswer3->SetBackgroundColor(FLinearColor(1, 0, 0, 1));
	}
	QuestionDelay();
}
void UTriviaWidget::CheckAnswer4()
{
	if (btnAnswer4->isRight) {
		rightAnswers++;
		btnAnswer4->SetBackgroundColor(FLinearColor(0, 1, 0, 1));
	}
	else {
		btnAnswer4->SetBackgroundColor(FLinearColor(1, 0, 0, 1));
	}
	QuestionDelay();
}
void UTriviaWidget::CheckAnswer5()
{
	if (btnAnswer5->isRight) {
		rightAnswers++;
		btnAnswer5->SetBackgroundColor(FLinearColor(0, 1, 0, 1));
	}
	else {
		btnAnswer5->SetBackgroundColor(FLinearColor(1, 0, 0, 1));
	}
	QuestionDelay();
}
void UTriviaWidget::ShowQuestion(Question question)
{
	lblQuestion->SetText(FText::FromString(question.question));

	TArray<Answer> answers;

	answers.Add(question.answer1);
	answers.Add(question.answer2);
	answers.Add(question.answer3);
	answers.Add(question.answer4);
	answers.Add(question.answer5);

	int index;

	index = FMath::RandRange(0, answers.Num() - 1);

	FLinearColor buttonBaseColor = FLinearColor(.8f, .8f, .8f, 1);

	lblAnswer1->SetText(FText::FromString(answers[index].text));
	btnAnswer1->isRight = answers[index].isTrue;
	btnAnswer1->SetBackgroundColor(buttonBaseColor);
	answers.RemoveAt(index);

	index = FMath::RandRange(0, answers.Num() - 1);
	lblAnswer2->SetText(FText::FromString(answers[index].text));
	btnAnswer2->isRight = answers[index].isTrue;
	btnAnswer2->SetBackgroundColor(buttonBaseColor);
	answers.RemoveAt(index);


	index = FMath::RandRange(0, answers.Num() - 1);
	lblAnswer3->SetText(FText::FromString(answers[index].text));
	btnAnswer3->isRight = answers[index].isTrue;
	btnAnswer3->SetBackgroundColor(buttonBaseColor);
	answers.RemoveAt(index);


	index = FMath::RandRange(0, answers.Num() - 1);
	lblAnswer4->SetText(FText::FromString(answers[index].text));
	btnAnswer4->isRight = answers[index].isTrue;
	btnAnswer4->SetBackgroundColor(buttonBaseColor);
	answers.RemoveAt(index);

	
	index = FMath::RandRange(0, answers.Num() - 1);
	lblAnswer5->SetText(FText::FromString(answers[index].text));
	btnAnswer5->isRight = answers[index].isTrue;
	btnAnswer5->SetBackgroundColor(buttonBaseColor);
	answers.RemoveAt(index);
}
FString UTriviaWidget::FormatTime(float timeS) {
	int32 totalTime = FMath::RoundToInt32(timeS);
	int32 minutes = totalTime / 60;
	int32 seconds = totalTime % 60;

	return FString::Printf(TEXT("%02d:%02d"), minutes, seconds);
}