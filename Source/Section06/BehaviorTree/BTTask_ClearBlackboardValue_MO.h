// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearBlackboardValue_MO.generated.h"

/**
 * Custom BehaviorTree task to clear out values in the BehaviorTree from C++.
 * Mostly used to unset the last known player location so that the AI will 
 * go back to patrolling.
 */
UCLASS()
class SECTION06_API UBTTask_ClearBlackboardValue_MO : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ClearBlackboardValue_MO();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
