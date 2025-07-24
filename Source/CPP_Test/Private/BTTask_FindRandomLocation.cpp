// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"

#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const enemy = cont->GetPawn())
		{
			auto const origin = enemy->GetActorLocation();
			if (auto* const navSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation loc;
				if (navSys->GetRandomPointInNavigableRadius(origin, searchRadius ,loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), loc.Location);
				}
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
