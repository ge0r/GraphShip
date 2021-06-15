// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Math/Vector.h"

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
	MoveTowardsDirection(DeltaTime);
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpaceShip::MoveTowardsDirection(float DeltaTime)
{
	FVector Location = GetActorLocation();
	Location += Direction * Speed *DeltaTime;
	SetActorLocation(Location);
}

// TODO Lerp towards rotation change
void ASpaceShip::RequestDirectionChange(FVector Dir) {
	if (Direction != Dir) {
		Direction = Dir;
		SetActorRotation(Direction.ToOrientationQuat(), ETeleportType::None);
	}
}

