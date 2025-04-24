// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun_MO.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

/**********************************************************************
 * Main class for our player and AI characters.  Use ACharacter instad
 * of APawn because ACharacter includes a built in movement component
 * that takes care of all of the movement functionality for us which 
 * the APawn does not.
 * *******************************************************************/

// Sets default values
AGun_MO::AGun_MO()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// We don't want to use the gun that's part of the model but 
	// use our own Actor so that they're swappable, so add the components
	// for the gun.
	// "RootComponent" already exists in parent Actor class so call it something else
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void AGun_MO::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AGun_MO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/***************************************************************************************
 * Allows us to pull the trigger from the ShooterCharacter or wherever we're binding input.
 * In this case it's ShooterCharacter.Shoot(). For the enemies it will be the AI.  
***************************************************************************************/
void AGun_MO::PullTrigger()
{	
	// Spawn a particle effect and sound effect
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
		
	FHitResult Hit;
	FVector ShotDirection;
	// Do a line trace for the fired shot
	bool bSuccess = GunTrace(Hit, ShotDirection);
	if(bSuccess)
	{		
		// Shot hit, so spawn a particle effect and play a hit sound
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

		// Check to see if the impact was an Actor			
		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{
			// Construct an instance of Unreal's built in damage system (built in damage system...wow)
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController *OwnerController = GetOwnerController();
			if(OwnerController == nullptr) return;
			// Send the damage event to the Actor taking the damage
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}		
}

AController* AGun_MO::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return nullptr;
	return OwnerPawn->GetController();	
}

/****************************************************************************
 * Handle the line trace for the fired bullet to check for impacts
*****************************************************************************/
bool AGun_MO::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{	
	AController *OwnerController = GetOwnerController();
	if(OwnerController == nullptr) return false;

	FVector Location;
	FRotator Rotation;	
	// Get the location/direction of the shot/trace based on where the player is looking.
	OwnerController->GetPlayerViewPoint(Location, Rotation);	
	ShotDirection = -Rotation.Vector();			
	// Rotation.Vector() gives you a vector pointing in the direction of this rotation.
	// Use this to find out the shot's max possible end location for the shot based on MaxRange
	FVector End = Location + (Rotation.Vector() * MaxRange);		

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);	// Make sure to not consider the gun or the player when line tracing
	Params.AddIgnoredActor(GetOwner());
	// Do the actual line trace
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);	
	return bSuccess;
}

