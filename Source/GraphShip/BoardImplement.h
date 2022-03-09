// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoardImplement.generated.h"

class ASpaceShip;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAPHSHIP_API UBoardImplement : public UActorComponent
{
	GENERATED_BODY()

private:
	// Declare a property of type blueprint, to spawn as class later
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_PointClass;

	// Declare a property of type blueprint, to spawn as class later
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_ShipClass;

	UPROPERTY(EditAnywhere)
	AActor* Camera;

	UPROPERTY(EditAnywhere)
    int Height;

	UPROPERTY(EditAnywhere)
    int Width;

	UPROPERTY(EditAnywhere)
    int Spacing;

	AActor*** Board;

	ASpaceShip *Ship = nullptr;
	bool Debug = false;
	FVector2D ShipCurrentCoords;
	FVector2D ShipNextCoords;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UBoardImplement();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void GenerateBoard();
	void SpawnShip();
	void InitializeCameraPosition();
	void UpdateShipPoints();

	AActor* GetPointFromCoords(FVector2D Coords);

};
