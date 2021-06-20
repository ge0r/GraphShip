// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShipRotatorComponent.h"
#include "SpaceShip.generated.h"

UCLASS()
class GRAPHSHIP_API ASpaceShip : public APawn
{
	GENERATED_BODY()

private:
	float Speed = 200;

	// TODO create c++ class for point
	AActor* CurrentPoint;
	USpaceShipRotatorComponent* LerpRotator = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector Direction = FVector(1, 0, 0);

	void FindNextPoint();
	void MoveToNextPoint(float DeltaTime);
	void MoveTowardsDirection(float DeltaTime);

	UFUNCTION(BLueprintCallable, Category = Custom)
	void RequestDirectionChange(FVector Direction);
};
