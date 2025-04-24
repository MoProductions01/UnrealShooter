// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocation_MO.generated.h"

/**
 * Sets the location of the Player in the Behavior Tree via C++
 */
UCLASS()
class SECTION06_API UBTService_PlayerLocation_MO : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
		UBTService_PlayerLocation_MO();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;	
};
