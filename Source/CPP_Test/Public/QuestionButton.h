// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "QuestionButton.generated.h"

/**
 * 
 */
UCLASS()
class CPP_TEST_API UQuestionButton : public UButton
{
	GENERATED_BODY()

public:
	bool isRight;
};
