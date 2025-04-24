// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot_MO.h"
#include "AIController.h"
#include "../ShooterCharacter_MO.h"

/**
 * BehaviorTree task that communicates with the BehaviorTree and handles shooting
 */
UBTTask_Shoot_MO::UBTTask_Shoot_MO()
{
    // Get the node name we want to interact with
     NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot_MO::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Bail if AI owner is null
    AAIController* AIController = OwnerComp.GetAIOwner();
    if(AIController == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    // Get a reference to the pawn that will be shooting
    AShooterCharacter_MO* Character = Cast<AShooterCharacter_MO>(AIController->GetPawn());
    if(Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // Have the AI shoot
    Character->Shoot();

    return EBTNodeResult::Succeeded;
}