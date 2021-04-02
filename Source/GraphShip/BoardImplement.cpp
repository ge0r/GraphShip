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
	FRotator myRot(0, 0, 0);
	FVector myLoc(0, 1, 0);
	UE_LOG(LogTemp, Warning, TEXT("Generating Board"));
	AActor* SpawnedPoint1 = (AActor*)GetWorld()->SpawnActor<AActor>(BP_PointClass, myLoc, myRot);
	AActor* SpawnedPoint2 = (AActor*)GetWorld()->SpawnActor<AActor>(BP_PointClass, myLoc*10, myRot);
	AActor* SpawnedPoint3 = (AActor*)GetWorld()->SpawnActor<AActor>(BP_PointClass, myLoc*100, myRot);
	AActor* SpawnedPoint4 = (AActor*)GetWorld()->SpawnActor<AActor>(BP_PointClass, myLoc*1000, myRot);
}
