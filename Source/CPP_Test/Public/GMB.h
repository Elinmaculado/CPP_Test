// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GMB.generated.h"


UCLASS()
class CPP_TEST_API AGMB : public AGameModeBase
{
	GENERATED_BODY()

public:
	int score = 0;
};
