// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShipRotatorComponent.h"
#include "SpaceShip.generated.h"

class APoint;

UCLASS()
class GRAPHSHIP_API ASpaceShip : public APawn
{
	GENERATED_BODY()

private:
	float Speed = 200;

	APoint *CurrentPoint;
	APoint *NextPoint;
	float MovementDuration = 0.5;
	float LerpMovementTimeElapsed = 0;
	bool ClampMovement = true;
	bool FlippedColors = false;
	USpaceShipRotatorComponent* LerpRotator = nullptr;

	FVector NextDirection = FVector(1, 0, 0);
	FVector CurrentDirection = NextDirection;
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

	bool HasReachedNextPoint = false;
	bool IsAlive = true;
	bool JustSpawned = true;

	void MoveToNextPoint(float DeltaTime);
	void SetCurrentPoint(APoint *Point);
	void SetNextPoint(APoint *Point);
	void FlipColors();
	void Die();
	void UpdateCurrentDirection();
	bool IsColorsFlipped();
	FVector GetCurrentDirection();
	FVector GetNextDirection();
	APoint* GetCurrentPoint();
	APoint* GetNextPoint();

	UFUNCTION(BLueprintCallable, Category = Custom)
	void RequestDirectionChange(FVector Direction);

	UFUNCTION(BlueprintImplementableEvent)
	void FlipColorsBPEvent();

};
