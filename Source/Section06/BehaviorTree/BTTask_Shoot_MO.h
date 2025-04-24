// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot_MO.generated.h"

/**
 * BehaviorTree task that communicates with the BehaviorTree and handles shooting
 */
UCLASS()
class SECTION06_API UBTTask_Shoot_MO : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Shoot_MO();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
