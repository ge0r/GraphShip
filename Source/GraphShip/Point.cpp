// Fill out your copyright notice in the Description page of Project Settings.


#include "Point.h"
#include "Point.h"

// Sets default values
APoint::APoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoint::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Spawning Point"));
	
}

// Called every frame
void APoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoint::SetIsVisited(bool Visited)
{
	IsVisited = Visited;
}

bool APoint::GetIsVisited()
{
	return IsVisited;
}

void APoint::SetDirectionVisited(FVector Direction)
{
	DirectionVisited = Direction;
}

FVector APoint::GetDirectionVisited()
{
	return DirectionVisited;
}

void APoint::SetDirectionTookOff(FVector Direction)
{
	DirectionTookOff = Direction;
}

FVector APoint::GetDirectionTookOff()
{
	return DirectionTookOff;
}

