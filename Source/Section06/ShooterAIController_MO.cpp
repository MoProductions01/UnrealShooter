// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController_MO.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter_MO.h"

/***********************************************************************
 * Class that handles the C++ side for the AI for the enemy characters.
 * Most of the logic is handled in the BehaviorTrees and Blackboards
************************************************************************/

void AShooterAIController_MO::BeginPlay()
{
    Super::BeginPlay();      

    if(AIBehavior != nullptr)
    {   // Start running the BehaviorTree which handles the enemy AI
        RunBehaviorTree(AIBehavior);
        // Setting Blackboard Keys for the AI to work with
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),
            PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),
            GetPawn()->GetActorLocation());
    }
    
}

void AShooterAIController_MO::Tick(float DeltaSeconds)
{
    // Not much to do here since the BehaviorTree handles the AI
    Super::Tick(DeltaSeconds);           
}

/**************************************************************************************************
 * Wrapper for the AI to just call the base character IsDead funtion, which just checks if the
 * Health is below 0
**************************************************************************************************/
bool AShooterAIController_MO::IsDead() const
{
    AShooterCharacter_MO* ControlledCharacter = Cast<AShooterCharacter_MO>(GetPawn());
    if(ControlledCharacter != nullptr)
    {
        // Just checks if the health is <= 0
        return ControlledCharacter->IsDead();        
    }
    
    // If not controlling a pawn then the controller is as good as dead.  A pawn
    // detatches from it's AI controller when it dies thnaks to our code.
    return true; 
}

