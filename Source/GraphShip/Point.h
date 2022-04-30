// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Point.generated.h"

UCLASS()
class GRAPHSHIP_API APoint : public AActor
{
	GENERATED_BODY()
	
private:
	FVector DirectionVisited;
	FVector DirectionTookOff;
	bool IsVisited;

public:	
	// Sets default values for this actor's properties
	APoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetIsVisited(bool Visited);
	bool GetIsVisited();
	void SetDirectionVisited(FVector Direction);
	FVector GetDirectionVisited();
	void SetDirectionTookOff(FVector Direction);
	FVector GetDirectionTookOff();
};
