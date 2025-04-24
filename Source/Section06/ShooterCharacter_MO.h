// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter_MO.generated.h"

/**********************************************************************
 * Main class for our player and AI characters.  Use ACharacter instad
 * of APawn because ACharacter includes a built in movement component
 * that takes care of all of the movement functionality for us which 
 * the APawn does not.
 * *******************************************************************/

class AGun_MO;
UCLASS()
class SECTION06_API AShooterCharacter_MO : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter_MO();	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Overriden function from Actor.h to recieve the damage from Gun_MO::PullTrigger
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	// Functions that communicates with the Blueprint section for the character's health.
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;

	// The function bound to the PullTrigger Action that then calls the Gun's PullTrigger function
	void Shoot();


private:
	// functions that are set up via the project settings Input Axis/Action values
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void Jump();
	
	UPROPERTY(EditAnywhere)
	float RotationRate = 10; // Rotation Rate for gamepad thumbsticks.  Multiply this by 
							 // the AxisValue to get a speed
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun_MO> GunClass; // Define the blueprint class (not the gun itself) we should spawn

	UPROPERTY()
	AGun_MO* Gun; // The gun we're going to spawn

	// Health values
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;
};
