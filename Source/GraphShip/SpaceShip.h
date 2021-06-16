// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"

UCLASS()
class GRAPHSHIP_API ASpaceShip : public APawn
{
	GENERATED_BODY()

private:
	float Speed = 200;
	FVector Direction = FVector(1, 0, 0);
	float LerpRotationDuration = 0.2;

	FQuat StartOrientation;
	FQuat EndOrientation;
	float LerpRotationTimeElapsed = 0;
	float ClampRotation = true;

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

	void MoveTowardsDirection(float DeltaTime);

	UFUNCTION(BLueprintCallable, Category = Custom)
	void RequestDirectionChange(FVector Direction);
};
