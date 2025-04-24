// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValue_MO.h"
#include "BehaviorTree/BlackboardComponent.h"


/**
 * Custom BehaviorTree task to clear out values in the BehaviorTree from C++.
 * Mostly used to unset the last known player location so that the AI will 
 * go back to patrolling.
 */
UBTTask_ClearBlackboardValue_MO::UBTTask_ClearBlackboardValue_MO()
{
    // "Clear Blackboard Value" is the name of the node in the BehaviorTree that we will
    // be interacting with
    NodeName = TEXT("Clear Blackboard Value");
}

/******************************************************************************
 * The only thing we need to do is execute a task, no need for ticks 
*******************************************************************************/
EBTNodeResult::Type UBTTask_ClearBlackboardValue_MO::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Clear the Blackboard value selected in the Behavior Tree
    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}