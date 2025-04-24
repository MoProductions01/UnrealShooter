// Fill out your copyright notice in the Description page of Project Settings.


#include "Section06PlayerController_MO.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


/**
 * This class handles the end game, including showing HUD items starting timers
 * to reset the behavior of the game
 */

void ASection06PlayerController_MO::BeginPlay()
{
    Super::BeginPlay();

    // Create the HUD wisget and show it on screen
    HUD = CreateWidget(this, HUDClass);
    if(HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}

/***********************************************************************************
 * Overridden PlayerController funtion that Handles end game logic such as who to 
 * focus on, which end game HUD screen to show and get timers going so the game can reset
************************************************************************************/
void ASection06PlayerController_MO::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    // 
    if(HUD != nullptr)
    {
        //HUD->RemoveFromViewport(); // deprecated
        HUD->RemoveFromParent();
    }
    
    // Display the correct end game screen depending on whether or not the Player is the winner
    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }
    
    // Get a timer going to restart the game after RestartDelay seconds
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);    
}