// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardImplement.h"

// Sets default values for this component's properties
UBoardImplement::UBoardImplement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBoardImplement::BeginPlay()
{
	Super::BeginPlay();

	GenerateBoard();
	SpawnShip();
	InitializeCameraPosition();
}


// Called every frame
void UBoardImplement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBoardImplement::GenerateBoard()
{
	UE_LOG(LogTemp, Warning, TEXT("Generating Board"));
	FRotator myRotation(0, 0, 0);

	int pointNum = Width * Height;
	int offsetX = Spacing * (int)(Width / 2);
	int offsetY = Spacing * (int)(Height / 2);

	// TODO Make this a 2d array
	AActor*** BoardPoints = new AActor** [Width];
	for (int i = 0; i < Width; i++) {
		BoardPoints[i] = new AActor* [Height];
	}

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			int xCoord = i * Spacing - offsetX;
			int yCoord = j * Spacing - offsetY;
			UE_LOG(LogTemp, Warning, TEXT("Generating Point at [%d, %d]"), xCoord, yCoord);
			FVector myLocation(xCoord, yCoord, 0);
			BoardPoints[i][j] = (AActor*)GetWorld()->SpawnActor<AActor>(BP_PointClass, myLocation, myRotation);
		}
	}
}

void UBoardImplement::SpawnShip()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Ship"));
	FRotator myRotation(0, 0, 0);
	FVector myLocation(0, 0 , 0);
	AActor* Ship = (AActor*)GetWorld()->SpawnActor<AActor>(BP_ShipClass, myLocation, myRotation);
}

void UBoardImplement::InitializeCameraPosition()
{
	Camera->SetActorLocation(FVector(0, 0, Width * Spacing));
}
