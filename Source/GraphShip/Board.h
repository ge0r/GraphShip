// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrailComponent.h"
#include "Board.generated.h"

class ASpaceShip;

UCLASS() 
class GRAPHSHIP_API ABoard : public AActor
{
	GENERATED_BODY()

private:
	// Declare a property of type blueprint, to spawn as class later
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_PointClass;

	// Declare a property of type blueprint, to spawn as class later
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_ShipClass;

	// Declare a property of type blueprint, to spawn as class later
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_TrailSegmentClass;

	UPROPERTY(EditAnywhere)
	AActor* Camera;

	UPROPERTY(EditAnywhere)
    int Height;

	UPROPERTY(EditAnywhere)
    int Width;

	UPROPERTY(EditAnywhere)
    int Spacing;

	AActor*** BoardGrid;
	ASpaceShip* Ship = nullptr;
	UTrailComponent* Trail = nullptr;
	bool Debug = false;
	FVector2D ShipCurrentCoords;
	FVector2D ShipNextCoords;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABoard();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GenerateBoard();
	void SpawnShip();
	void InitializeCameraPosition();
	void UpdateShipPoints();
	AActor* GetPointFromCoords(FVector2D Coords);
};
