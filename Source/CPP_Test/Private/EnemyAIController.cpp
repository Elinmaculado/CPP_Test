// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "MyEnemy.h"

AEnemyAIController::AEnemyAIController(FObjectInitializer const& ObjectInitializer)
{
	
}

void AEnemyAIController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	if (AMyEnemy* const enemy = Cast<AMyEnemy>(NewPawn))
	{
		if (UBehaviorTree* const tree = enemy->GetBeahBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}
