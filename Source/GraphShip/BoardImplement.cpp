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
	
}


// Called every frame
void UBoardImplement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBoardImplement::GenerateBoard()
{
	FRotator myRotation(0, 0, 0);
	UE_LOG(LogTemp, Warning, TEXT("Generating Board"));
	FVector myLoc(10, 10 , 0);

	int pointNum = Width * Height;
	AActor** BoardPoints = new AActor* [pointNum];
	int count = 0;

	for (int i=0; i<Height; i++) {
		for (int j = 0; j < Width; j++) {
			FVector myLocation(i * Spacing, j *Spacing , 0);
			UE_LOG(LogTemp, Warning, TEXT("Generating Point %d"), count);

			BoardPoints[count] = (AActor*)GetWorld()->SpawnActor<AActor>(BP_PointClass, myLocation, myRotation);
			count++;
		}
	}
}
