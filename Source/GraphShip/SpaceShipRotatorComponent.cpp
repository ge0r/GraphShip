// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipRotatorComponent.h"
#include "SpaceShip.h"

// Sets default values for this component's properties
USpaceShipRotatorComponent::USpaceShipRotatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpaceShipRotatorComponent::BeginPlay()
{
	Super::BeginPlay();

	ASpaceShip* Owner = (ASpaceShip*) GetOwner();
	StartOrientation = Owner->GetActorRotation().Quaternion();
	EndOrientation = Owner->NextDirection.ToOrientationQuat();
}


// Called every frame
void USpaceShipRotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleRotation(DeltaTime);
}

void USpaceShipRotatorComponent::Reset()
{
	ASpaceShip* Owner = (ASpaceShip*) GetOwner();

	StartOrientation = Owner->GetActorRotation().Quaternion();
	EndOrientation = Owner->NextDirection.ToOrientationQuat();

	// Reset time to lerp rotation, in order to start rotating
	LerpRotationTimeElapsed = 0;
	// Reset clamping
	ClampRotation = true;

	//UE_LOG(LogTemp, Warning, TEXT("StartOrientation: %s EndOrientation: %s"), *StartOrientation.Euler().ToString(), *EndOrientation.Euler().ToString());
}

void USpaceShipRotatorComponent::HandleRotation(float DeltaTime) 
{
	ASpaceShip* Owner = (ASpaceShip*) GetOwner();

	// If you still have to rotate, lerp towards rotation target
	if (LerpRotationTimeElapsed < RotationDuration) {
		Owner->SetActorRotation(FMath::Lerp(StartOrientation, EndOrientation, LerpRotationTimeElapsed / RotationDuration));

		// Keep track of elapsed time
		LerpRotationTimeElapsed += DeltaTime;
	}
	// Otherwise, clamp actor rotation only once
	else if (ClampRotation) {
		// Clamp the rotation to the required value if Lerping is done
		Owner->SetActorRotation(Owner->NextDirection.ToOrientationQuat());
		//UE_LOG(LogTemp, Warning, TEXT("Actor clamped to %s"), *Owner->GetActorRotation().Euler().ToString());
		ClampRotation = false;
	}
}
