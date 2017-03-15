// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pattern.h"
#include "PointPlotter.generated.h"

UCLASS()
class POINTSPAWNER_API APointPlotter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointPlotter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// called by timer on each tick
	void AdvanceTimer();

	void SpawnTimerHasFinished();

	FTimerHandle SpawnTimerHandle;

	int32 CurrentTime;

	int32 NumberOfPoints;

	Pattern* RandomPath;

};


