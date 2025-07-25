// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class CPP_TEST_API UBTTask_FindPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_FindPlayerLocation(FObjectInitializer const& FObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Search", meta=(AllowPrivateAccess = "true"))
	bool SearchRandom = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Search", meta=(AllowPrivateAccess = "true"))
	float searchRadius = 150.f;
};
