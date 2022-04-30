// Fill out your copyright notice in the Description page of Project Settings.


#include "TrailComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UTrailComponent::UTrailComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTrailComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTrailComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTrailComponent::GenerateSegment(AActor* FirstPoint, AActor* SecondPoint, bool FlippedColor, TSubclassOf<class AActor> BP_TrailSegmentClass)
{
	//DrawDebugLine(GetWorld(), FirstPoint->GetActorLocation(), SecondPoint->GetActorLocation(), FColor(255, 0, 0), true, 2, 0U, 24);
	FVector Angle = SecondPoint->GetActorLocation() - FirstPoint->GetActorLocation();
	FRotator Rotation = FRotationMatrix::MakeFromX(Angle).Rotator();
	AActor* Trail = GetWorld()->SpawnActor<AActor>(BP_TrailSegmentClass, FirstPoint->GetActorLocation(), Rotation);

	if (FlippedColor) {
		FRotator NewRotation = FRotator(0, 0, 180);
		FQuat QuatRotation = FQuat(NewRotation);
		Trail->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
	}
}

