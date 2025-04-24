// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation_MO.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"

/**
 * Sets the location of the Player in the Behavior Tree via C++
 */

UBTService_PlayerLocation_MO::UBTService_PlayerLocation_MO()
{
    // Get the node from the Behavior Tree
    NodeName = TEXT("Update Player Location");
}

void UBTService_PlayerLocation_MO::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Update the BehaviorTree's player location as long as the PlayerPawn exists
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(PlayerPawn == nullptr)
    {
        return;
    }
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}