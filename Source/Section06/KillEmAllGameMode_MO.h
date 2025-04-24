// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Section06GameModeBase.h"
#include "KillEmAllGameMode_MO.generated.h"

/**
 * There can be many game modes but for this course it's just kill everything you can see.
 * Here is where we handle both a Pawn being killed and the game ending
 */
UCLASS()
class SECTION06_API AKillEmAllGameMode_MO : public ASection06GameModeBase
{
	GENERATED_BODY()

public:
	// Handle a Pawn being killed
	virtual void PawnKilled(APawn* PawnKilled) override;	
	
private:
	// Handle the game ending
	void EndGame(bool bIsPlayerWinner);	
};
