// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "SpaceShip.h"

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
	UpdateShipPoints();
	InitializeCameraPosition();
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Ship->IsAlive) {
		if (Ship->HasReachedNextPoint) {
			if (!Ship->JustSpawned) {
				Trail->GenerateSegment(GetPointFromCoords(ShipCurrentCoords), GetPointFromCoords(ShipNextCoords));
			}
			UpdateShipPoints();
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

	BoardGrid = new AActor** [Width];
	for (int i = 0; i < Width; i++) {
		BoardGrid[i] = new AActor* [Height];
	}
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			int xCoord = i * Spacing - offsetX;
			int yCoord = j * Spacing - offsetY;
			if (Debug) UE_LOG(LogTemp, Warning, TEXT("Generating Point at [%d, %d]"), xCoord, yCoord);
			FVector myLocation(xCoord, yCoord, 0);
			// Spawn a BP_Point Actor
			BoardGrid[i][j] = (AActor*)GetWorld()->SpawnActor<AActor>(BP_PointClass, myLocation, myRotation);
			// Make each Point a child of this component's owner (BP_Board Actor)
			BoardGrid[i][j]->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
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

void ABoard::UpdateShipPoints()
{
	ShipCurrentCoords = ShipNextCoords;
	Ship->SetCurrentPoint(GetPointFromCoords(ShipCurrentCoords));

	ShipNextCoords = ShipCurrentCoords + FVector2D(Ship->NextDirection.X, Ship->NextDirection.Y);
	if (((ShipNextCoords.X < 0) || (ShipNextCoords.X >= Height)) || ((ShipNextCoords.Y < 0) || (ShipNextCoords.Y >= Width))) {
		Ship->Die();
	}
	else {
		Ship->SetNextPoint(GetPointFromCoords(ShipNextCoords));
		Ship->HasReachedNextPoint = false;
		//FString ScreenMsg = FString::Printf(TEXT("Ship's next Direction is: %s || Next Coords are: %s"), *Ship->NextDirection.ToString(), *ShipNextCoords.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ScreenMsg);
	}
}

AActor* ABoard::GetPointFromCoords(FVector2D Coords)
{
	AActor* Point = BoardGrid[int(Coords.X)][int(Coords.Y)];
	//UE_LOG(LogTemp, Warning, TEXT("Next point is actor %s"), *Point->GetName());
	return Point;

}

