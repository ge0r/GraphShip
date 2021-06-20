// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Math/Vector.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LerpRotator = CreateDefaultSubobject<USpaceShipRotatorComponent>(FName("LerpRotator Component"));
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindNextPoint();
	MoveToNextPoint(DeltaTime);
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// TODO implement find next point
void ASpaceShip::FindNextPoint()
{

}

void ASpaceShip::MoveToNextPoint(float DeltaTime)
{
	// TODO Check if next point requires a direction change
	MoveTowardsDirection(DeltaTime);
}

void ASpaceShip::MoveTowardsDirection(float DeltaTime)
{
	FVector Location = GetActorLocation();
	Location += Direction * Speed *DeltaTime;
	SetActorLocation(Location);
}


// RequestDirectionChange is called from blueprints, via the BP_SpaceShip class 
void ASpaceShip::RequestDirectionChange(FVector Dir) {
	// If the requsted direction is not the same as the current direction, change direction
	if (Direction != Dir) {
		UE_LOG(LogTemp, Warning, TEXT("Direction changes"));
		Direction = Dir;

		// Reset the Lerp Rotator component
		LerpRotator->Reset();
	}
}

