// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Multiplayer.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();
	
	UPROPERTY(EditAnywhere, Category = "Mesh Configs")
	float Speed = 20;

	UPROPERTY(EditAnywhere, Category = "Mesh Configs", Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	// Should Patrol between start and target locations
	UPROPERTY(EditAnywhere, Category = "Mesh Configs")
	bool Patrol;
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:
	float DistanceBetweenLocations = 0;
	FVector StartLocation;
	FVector CurrentDestLocation;

	bool ReachedDestLocation();
	void ChangeDestLocation();
};
