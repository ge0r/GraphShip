// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardImplement.h"
#include "SpaceShip.h"

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

	if (Ship) {
		Ship->TeleportCall();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Ship not initialized"));
	}
}


// Called every frame
void UBoardImplement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBoardImplement::GenerateBoard()
{
	UE_LOG(LogTemp, Warning, TEXT("Generating Board"));
	FRotator myRotation(0, 0, 0);

	int pointNum = Width * Height;
	int offsetX = Spacing * (int)(Width / 2);
	int offsetY = Spacing * (int)(Height / 2);

	AActor*** Board = new AActor** [Width];
	for (int i = 0; i < Width; i++) {
		Board[i] = new AActor* [Height];
	}

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			int xCoord = i * Spacing - offsetX;
			int yCoord = j * Spacing - offsetY;
			if (Debug) UE_LOG(LogTemp, Warning, TEXT("Generating Point at [%d, %d]"), xCoord, yCoord);
			FVector myLocation(xCoord, yCoord, 0);
			// Spawn a BP_Point Actor
			Board[i][j] = (AActor*)GetWorld()->SpawnActor<AActor>(BP_PointClass, myLocation, myRotation);
			// Make each Point a child of this component's owner (BP_Board Actor)
			Board[i][j]->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void UBoardImplement::SpawnShip()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Ship"));
	FRotator myRotation(0, 0, 0);
	FVector myLocation(0, 0 , 0);
	Ship = GetWorld()->SpawnActor<ASpaceShip>(BP_ShipClass, myLocation, myRotation);
}

void UBoardImplement::InitializeCameraPosition()
{
	Camera->SetActorLocation(FVector(0, 0, Width * Spacing));
}
