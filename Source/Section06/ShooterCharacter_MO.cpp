// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter_MO.h"
#include "Gun_MO.h"
#include "Components/CapsuleComponent.h"
#include "Section06GameModeBase.h"

/*************************************************************************
 * This class is used to replace the gun that came with the Wraith model.  
 * We want to use our own Actor for modularity and custom control.
*************************************************************************/

// Sets default values
AShooterCharacter_MO::AShooterCharacter_MO()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter_MO::BeginPlay()
{
	Super::BeginPlay();	
	// Spawn the gun Actor based on the Blueprint class at runtime instead 
	// of using the gun that came with the model
	Gun = GetWorld()->SpawnActor<AGun_MO>(GunClass);
	// Get the gun bone that's already a part of the ShooterCharacter (weapon_r) and hide it
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	// Add our gun Actor the socket that we created on the mesh
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket_MO"));
	Gun->SetOwner(this);

	// Give the character their starting health
	Health = MaxHealth;
}

// Called every frame
void AShooterCharacter_MO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*********************************************************************************************
 * Overridded callback function from Actor.h for Actors to take damage.  Called from the engine
 * after we call TakeDamage() from Gun.cpp
**********************************************************************************************/
float AShooterCharacter_MO::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	// Call the parent version to allow the system to let us know how much damage to apply.
	// Should be the same as DamageAmount but not always
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	// If the DamageToApply is more than the health clamp it to the Health itself
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	
	// Handle a few things if the character is dead
	if(IsDead())
	{				
		// Get a pointer to the game mode so we can handle the logic of the pawn being killed
		ASection06GameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASection06GameModeBase>();
		if(GameMode != nullptr)
		{
			// Let the game mode know that the pawn is killed so it can handle the appropriate logic
			GameMode->PawnKilled(this);
		}
		// Character is dead, so remove controller so, for example AI won't keep shooting
		DetachFromControllerPendingDestroy(); 
		// Turn off the collision so the character is no longer able to impact the game world
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

// These are the BlueprintPure functions that deal with the character's Health and living/dead state
bool AShooterCharacter_MO::IsDead() const
{
	return Health <= 0;
}
float AShooterCharacter_MO::GetHealthPercentage() const
{
	return Health/MaxHealth;
}

// Called to bind functionality to input
void AShooterCharacter_MO::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);	

	// Bind all of the Axis and Action values to their various functions.  
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter_MO::MoveForward);	
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter_MO::LookUp);	
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter_MO::MoveRight);	
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter_MO::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter_MO::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter_MO::LookRightRate);		
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AShooterCharacter_MO::Jump);			
	PlayerInputComponent->BindAction(TEXT("PullTrigger"), EInputEvent::IE_Pressed, this, &AShooterCharacter_MO::Shoot);	
}


// All of these are just wrapper functions for engine calls but I prefer to
// use my own functions just in case I want to do something else or print debug information
void AShooterCharacter_MO::Shoot()
{
	Gun->PullTrigger();
}
void AShooterCharacter_MO::Jump()
{
	ACharacter::Jump();
}
void AShooterCharacter_MO::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}
void AShooterCharacter_MO::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}
void AShooterCharacter_MO::LookUp(float AxisValue)
{	
	AddControllerPitchInput(AxisValue);
}
void AShooterCharacter_MO::LookRight(float AxisValue)
{	
	AddControllerYawInput(AxisValue);
}

// These next two functions are used by the controller, which handles differently
// than a mouse.  A mouse is in motion when moving, a controller thumb stick
// could just be sitting there in one spot.  You need to multiply the AxisValue
// by a RotationRate to get a speed.  In order to make that speed frame rate 
// independent you multiply it by "DeltaTime" to get the distance
void AShooterCharacter_MO::LookUpRate(float AxisValue)
{		
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}
void AShooterCharacter_MO::LookRightRate(float AxisValue)
{		
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}