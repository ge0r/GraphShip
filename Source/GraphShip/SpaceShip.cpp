// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	// TODO set direction based on InputAction from Blueprint
	FVector Direction = FVector(1, 0, 0);
	MoveTowardsDirection(Direction, DeltaTime);
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpaceShip::MoveTowardsDirection(FVector Direction, float DeltaTime)
{
	FVector Location = GetActorLocation();
	Location += Direction * Speed *DeltaTime;
	SetActorLocation(Location);
}
