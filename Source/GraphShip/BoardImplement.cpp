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
}


// Called every frame
void UBoardImplement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Ship->HasReachedNextPoint) {
		UpdateShipPoints();
	}
	Ship->MoveToNextPoint(DeltaTime);
}

void UBoardImplement::GenerateBoard()
{
	UE_LOG(LogTemp, Warning, TEXT("Generating Board"));
	FRotator myRotation(0, 0, 0);

	int pointNum = Width * Height;
	int offsetX = Spacing * (int)(Width / 2);
	int offsetY = Spacing * (int)(Height / 2);

	Board = new AActor** [Width];
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
	FRotator SpawnRotation(0, 0, 0);

	// Choose the SpawnPoint.
	// For now the SpawnPoint is in the middle of the board.
	FVector2D BoardSpawnCoords = FVector2D(int(Height / 2), int(Width / 2));
	AActor* SpawnPoint = Board[int(BoardSpawnCoords.X)][int(BoardSpawnCoords.Y)];
	FVector SpawnLocation = SpawnPoint->GetActorLocation();
	Ship = GetWorld()->SpawnActor<ASpaceShip>(BP_ShipClass, SpawnLocation, SpawnRotation);
	ShipNextCoords = BoardSpawnCoords;
	UpdateShipPoints();
}

void UBoardImplement::InitializeCameraPosition()
{
	Camera->SetActorLocation(FVector(0, 0, Width * Spacing));
}

// Updates the Ship's next and current point
void UBoardImplement::UpdateShipPoints()
{
	ShipCurrentCoords = ShipNextCoords;
	Ship->SetCurrentPoint(GetPointFromCoords(ShipCurrentCoords));

	ShipNextCoords = ShipCurrentCoords + FVector2D(Ship->NextDirection.X, Ship->NextDirection.Y);
	Ship->SetNextPoint(GetPointFromCoords(ShipNextCoords));
	Ship->HasReachedNextPoint = false;


	// Print Ship direction and next point on screen
	FString ScreenMsg = FString::Printf(TEXT("Ship's next Direction is: %s || Next Coords are: %s"), *Ship->NextDirection.ToString(), *ShipNextCoords.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ScreenMsg);

	// DEBUG: Change the color of the next point
}

AActor* UBoardImplement::GetPointFromCoords(FVector2D Coords)
{	
	AActor* Point = Board[int(Coords.X)][int(Coords.Y)];
	//UE_LOG(LogTemp, Warning, TEXT("Next point is actor %s"), *Point->GetName());

	return Point;
}
