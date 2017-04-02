// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyStructsAndEnums.h"
#include "GameFramework/Actor.h"
#include "Pattern.h"
#include "RandomPath.h"
#include "Kismet/GameplayStatics.h"
#include "PointPlotter.generated.h"

UCLASS()
class POINTSPAWNER_API APointPlotter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointPlotter();

	void PlotPattern(Pattern* PatternToPlot);

	void TeardownPattern();

	void TogglePointLocations();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// called by timer on each tick
	void AdvanceTimer();

	void SpawnTimerHasFinished();

	FTimerHandle m_SpawnTimerHandle;

	int32 m_CurrentTime;

	Pattern* m_Pattern;

	UParticleSystem* m_Sparker;

	UParticleSystem* m_Beam;
	
};


