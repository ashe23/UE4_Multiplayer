// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "DrawDebugHelpers.h"

AMovingPlatform::AMovingPlatform()
{
	Patrol = true;
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector CurrentLocation = GetActorLocation();
		FVector Direction = CurrentDestLocation - CurrentLocation;
		Direction.Normalize();
  		
		if (!ReachedDestLocation())
		{
			DrawDebugLine(
				GetWorld(),
				CurrentLocation,
				CurrentDestLocation,
				FColor(255, 0, 0),
				false, -1, 0,
				5.0f
			);

			CurrentLocation += Speed * DeltaTime * Direction;
			SetActorLocation(CurrentLocation, false, nullptr, ETeleportType::None);
			
		}
		else
		{
			if (Patrol)
			{
				ChangeDestLocation();
			}
		}		
	}

}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	// change location from relative to world
	TargetLocation = GetTransform().TransformPosition(TargetLocation);	
	CurrentDestLocation = TargetLocation;

	// decide distance between start and target points
	DistanceBetweenLocations = FVector::Dist(StartLocation, TargetLocation);

	SetReplicates(true);
	SetReplicateMovement(true);
}

bool AMovingPlatform::ReachedDestLocation()
{
	if (CurrentDestLocation == StartLocation)
	{
		return FVector::Dist(TargetLocation, GetActorLocation()) >= DistanceBetweenLocations;
	}
	else
	{
		return FVector::Dist(StartLocation, GetActorLocation()) >= DistanceBetweenLocations;
	}
}

void AMovingPlatform::ChangeDestLocation()
{
	CurrentDestLocation = (CurrentDestLocation == StartLocation) ? TargetLocation : StartLocation;
}
