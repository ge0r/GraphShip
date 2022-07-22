// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "SpaceShip.h"
#include "Point.h"
#include "Square.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trail = CreateDefaultSubobject<UTrailComponent>(FName("Trail Component"));
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();

	GenerateBoard();
	SpawnShip();
	UpdatePoints();
	InitializeCameraPosition();
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Ship->IsAlive) {
		if (Ship->HasReachedNextPoint) {
			if (!Ship->JustSpawned) {
				Trail->GenerateSegment(GetPointFromCoords(ShipCurrentCoords), GetPointFromCoords(ShipNextCoords), Ship->IsColorsFlipped(), BP_TrailSegmentClass);
			}
			CheckPointCollision();
			// TODO create surface field here
			UpdatePoints();
			Ship->UpdateCurrentDirection();
			
			if (PointJustRevisited) {
				// Only flip colors when revisiting a point with recent visited direction same as the recent took off direction
				if (Ship->GetCurrentPoint()->GetDirectionVisited() == Ship->GetCurrentPoint()->GetDirectionTookOff()) {
					Ship->FlipColors();
				}
				PointJustRevisited = false;
			}
		}
		Ship->MoveToNextPoint(DeltaTime);

	}
}

void ABoard::GenerateBoard()
{
	UE_LOG(LogTemp, Warning, TEXT("Generating Board"));
	FRotator myRotation(0, 0, 0);
	int pointNum = Width * Height;
	int offsetX = Spacing * (int)(Width / 2);
	int offsetY = Spacing * (int)(Height / 2);

	BoardGrid = new APoint** [Width];
	BoardSquares = new ASquare** [Width];
	for (int i = 0; i < Width; i++) {
		BoardGrid[i] = new APoint* [Height];
		BoardSquares[i] = new ASquare* [Height];
	}
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			int xCoord = i * Spacing - offsetX;
			int yCoord = j * Spacing - offsetY;
			UE_LOG(LogTemp, Warning, TEXT("Generating Point at [%d, %d]"), xCoord, yCoord);
			FVector myLocation(xCoord, yCoord, 0);
			// Spawn a BP_Point Actor
			BoardGrid[i][j] = (APoint*)GetWorld()->SpawnActor<APoint>(BP_PointClass, myLocation, myRotation);
			BoardSquares[i][j] = (ASquare*)GetWorld()->SpawnActor<ASquare>(BP_SquareClass, myLocation, myRotation);
			// Make each Point a child of this component's owner (BP_Board Actor)
			BoardGrid[i][j]->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
			BoardSquares[i][j]->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void ABoard::SpawnShip()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Ship"));
	FRotator SpawnRotation(0, 0, 0);

	// Choose the SpawnPoint.
	// For now the SpawnPoint is in the middle of the board.
	FVector2D BoardSpawnCoords = FVector2D(int(Height / 2), int(Width / 2));
	AActor* SpawnPoint = BoardGrid[int(BoardSpawnCoords.X)][int(BoardSpawnCoords.Y)];
	FVector SpawnLocation = SpawnPoint->GetActorLocation();
	Ship = GetWorld()->SpawnActor<ASpaceShip>(BP_ShipClass, SpawnLocation, SpawnRotation);
	ShipNextCoords = BoardSpawnCoords;
}

void ABoard::InitializeCameraPosition()
{
	Camera->SetActorLocation(FVector(0, 0, Width * Spacing));
}

// Updates ship's current and next Points, and sets current Point as visited
void ABoard::UpdatePoints()
{
	ShipCurrentCoords = ShipNextCoords;
	APoint* CurrentPoint = GetPointFromCoords(ShipCurrentCoords);
	Ship->SetCurrentPoint(CurrentPoint);

	CurrentPoint->SetIsVisited(true);
	CurrentPoint->SetDirectionVisited(Ship->GetCurrentDirection());
	CurrentPoint->SetDirectionTookOff(Ship->GetNextDirection());

	ShipNextCoords = ShipCurrentCoords + FVector2D(Ship->GetNextDirection().X, Ship->GetNextDirection().Y);
	// If the Ship's next Coordinates are off limit, die
	if (((ShipNextCoords.X < 0) || (ShipNextCoords.X >= Height)) || ((ShipNextCoords.Y < 0) || (ShipNextCoords.Y >= Width))) {
		Ship->Die();
	}
	else {
		Ship->SetNextPoint(GetPointFromCoords(ShipNextCoords));
		Ship->HasReachedNextPoint = false;
	}
}

void ABoard::CheckPointCollision()
{
	APoint* NextPoint = GetPointFromCoords(ShipNextCoords);
	
	if (NextPoint->GetIsVisited())
	{
		PointJustRevisited = true;
		FVector ShipNextDirection = Ship->GetNextDirection();
		// If the Ship will leave the point in a direction similar to a took off direction or opposite to a visited direction,
		// then it crashes and dies
		if ((ShipNextDirection == -NextPoint->GetDirectionVisited()) || (ShipNextDirection == NextPoint->GetDirectionTookOff())) {
			Ship->Die();
			// Print crash status on screen
			FString ScreenMsg = FString::Printf(TEXT("You crashed in coordinates %s"), *ShipNextCoords.ToString());
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, ScreenMsg);
		}
	}
}

APoint* ABoard::GetPointFromCoords(FVector2D Coords)
{
	APoint* Point = BoardGrid[int(Coords.X)][int(Coords.Y)];
	//UE_LOG(LogTemp, Warning, TEXT("Next point is actor %s"), *Point->GetName());
	return Point;

}

