// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController_MO.generated.h"

/***********************************************************************
 * Class that handles the C++ side for the AI for the enemy characters.
 * Most of the logic is handled in the BehaviorTrees and Blackboards
************************************************************************/
UCLASS()
class SECTION06_API AShooterAIController_MO : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead() const;
	
protected:
	virtual void BeginPlay() override;

private:
	// The BehaviorTree that handles the AI logic for the enemy characters	
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
	
};
