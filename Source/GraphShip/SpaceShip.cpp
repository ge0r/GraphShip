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
	StartOrientation = GetActorRotation().Quaternion();
	EndOrientation = Direction.ToOrientationQuat();
	
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTowardsDirection(DeltaTime);

	// Lerp towards rotation change
	if (LerpRotationTimeElapsed < LerpRotationDuration) {
		SetActorRotation(FMath::Lerp(StartOrientation, EndOrientation, LerpRotationTimeElapsed / LerpRotationDuration));

		// Keep track of elapsed time
		LerpRotationTimeElapsed += DeltaTime;
	}
	else if (ClampRotation){
		// Clamp the rotation to the required value if Lerping is done
		SetActorRotation(Direction.ToOrientationQuat());
		UE_LOG(LogTemp, Warning, TEXT("Actor clamped to %s"), *GetActorRotation().Euler().ToString());
		ClampRotation = false;
	}
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

void ASpaceShip::RequestDirectionChange(FVector Dir) {
	if (Direction != Dir) {
		UE_LOG(LogTemp, Warning, TEXT("Direction change"));
		Direction = Dir;
		StartOrientation = GetActorRotation().Quaternion();
		EndOrientation = Direction.ToOrientationQuat();

		UE_LOG(LogTemp, Warning, TEXT("StartOrientation: %s EndOrientation: %s"), *StartOrientation.Euler().ToString(), *EndOrientation.Euler().ToString());

		// Reset time to lerp rotation
		LerpRotationTimeElapsed = 0;
		// Reset clamping
		ClampRotation = true;
	}
}

