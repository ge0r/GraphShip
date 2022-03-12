// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"

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

	// Do nothing for now, movement calls are handled by BoardImplement
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpaceShip::MoveToNextPoint(float DeltaTime)
{
	if (LerpMovementTimeElapsed < MovementDuration) {
		HasReachedNextPoint = false;
		
		SetActorLocation(FMath::Lerp<FVector>(CurrentPoint->GetActorLocation(), NextPoint->GetActorLocation(), LerpMovementTimeElapsed / MovementDuration));
		LerpMovementTimeElapsed += DeltaTime;
	}
	else {
		LerpMovementTimeElapsed = 0;
		HasReachedNextPoint = true;

		if (JustSpawned) {
			JustSpawned = false;
		}
	}
}

void ASpaceShip::SetCurrentPoint(AActor *Point)
{
	CurrentPoint = Point;
}

void ASpaceShip::SetNextPoint(AActor *Point)
{
	NextPoint = Point;
}

void ASpaceShip::Die()
{
	IsAlive = false;
}

// RequestDirectionChange is called from blueprints, via the BP_SpaceShip class 
void ASpaceShip::RequestDirectionChange(FVector Dir) {
	// If the requsted direction is not the same as the current direction, change direction
	if (NextDirection != Dir) {
		//UE_LOG(LogTemp, Warning, TEXT("Direction changes"));
		NextDirection = Dir;

		// Reset the Lerp Rotator component
		LerpRotator->Reset();
	}
}

