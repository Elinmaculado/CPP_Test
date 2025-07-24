// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
class UTriviaWidget;
class UTriviaMainMenu;
class UTriviaPause;
struct Score;
#include "GameFramework/GameModeBase.h"
#include "TriviaGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPP_TEST_API ATriviaGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


public: 
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UTriviaWidget> triviaWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UTriviaMainMenu> triviaMenuClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UTriviaPause> triviaPauseClass;

	UFUNCTION()
	void Play();

	UFUNCTION()
	void Menu();
	UFUNCTION()
	void Pause();
	UFUNCTION()
	void Resume();
	UFUNCTION()
	void Restart();

	void UpdateScore(int score, float time);

	UPROPERTY(EditAnywhere)
	USoundWave* levelMusic;

private:
	UTriviaWidget* triviaWidgetInstance;
	UTriviaMainMenu* triviaMenuInstance;
	UTriviaPause* triviaPauseInstance;
};
