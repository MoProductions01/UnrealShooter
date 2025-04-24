// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun_MO.generated.h"

/*************************************************************************
 * This class is used to replace the gun that came with the Wraith model.  
 * We want to use our own Actor for modularity and custom control.
*************************************************************************/

UCLASS()
class SECTION06_API AGun_MO : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun_MO();

	// Allows us to pull the trigger from the ShooterCharacter or wherever 
	// we're binding input. In this case it's ShooterCharacter.Shoot()
	// For the enemies it will be the AI
	void PullTrigger(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

private:
	// Components for the gun Actor to replace the gun that's part of the model
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp; // "RootComponent" already exists in parent Actor class so call it something else

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;	

	// Visual effects
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	// Sounds
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	// Gun stats
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	// Hanldes the line trace for the fired shot to check for collisions
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;
};
