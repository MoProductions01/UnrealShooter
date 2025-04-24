// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode_MO.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController_MO.h"

/**
 * There can be many game modes but for this course it's just kill everything you can see.
 * Here is where we handle both a Pawn being killed and the game ending
 */

/**********************************************************************************
 * Handle all of the necessary functinality when a pawn is killed, including ending the game
*************************************************************************************/
void AKillEmAllGameMode_MO::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    // If the player is killed, then it's game over right away
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController != nullptr)
    {        
        EndGame(false);
    }    

    // Iterate over the enemy controllers.  If any of them are alive then
    // the game is not over so just bail and let the game continue
    for(AShooterAIController_MO* Controller : TActorRange<AShooterAIController_MO>(GetWorld()))
    {
        if(!Controller->IsDead())
        {
            return;
        }
    }

    // If we've reached here then no enemy controllers are alive so end the game with a victory
    EndGame(true);        
}
/********************************************************************************
 * Handles ending the game, including letting the game know whether or not it was
 * the Player who won
********************************************************************************/
void AKillEmAllGameMode_MO::EndGame(bool bIsPlayerWinner)
{
    // Handle the actual ending of the game based on whether it was the Player or not
    for(AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = (Controller->IsPlayerController() == bIsPlayerWinner);
        // Let the end game situation know who to focus on
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}