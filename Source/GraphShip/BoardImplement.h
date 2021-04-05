// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoardImplement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAPHSHIP_API UBoardImplement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBoardImplement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void GenerateBoard();
	void SpawnShip();

private:
	// Declare a property of type blueprint, to spawn as class later
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_PointClass;

	// Declare a property of type blueprint, to spawn as class later
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_ShipClass;

	UPROPERTY(EditAnywhere)
    int Height;

	UPROPERTY(EditAnywhere)
    int Width;

	UPROPERTY(EditAnywhere)
    int Spacing;
};
