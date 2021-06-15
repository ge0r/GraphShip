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
	UPROPERTY(EditAnywhere)
	float Speed = 50;
	FVector Direction = FVector(1, 0, 0);

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