// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "Pattern.h"

Pattern::Pattern(UParticleSystem* Sparker, UParticleSystem* Beam, int32 NumberOfPoints)
{
	mySparker = Sparker;
	myBeam = Beam;
	this->NumberOfPoints = NumberOfPoints;
}

Pattern::Pattern()
{
}

Pattern::~Pattern()
{
	mySparker = nullptr;
	myBeam = nullptr;
	newPoints.Empty();
	newBeams.Empty();
}

void Pattern::GeneratePattern()
{
	for (int32 n = 0; n < NumberOfPoints; n++)
	{
		FVector newRandomLocation((n * FMath::RandRange(20.0f, 40.0f)), (n * FMath::RandRange(20.0f, 40.0f)), (n * FMath::RandRange(20.0f, 40.0f)));
		FMyPoint newPoint(newRandomLocation);
		newPoints.Add(newPoint);

	}

	for (int32 n = 0; n < newPoints.Num() - 1; n++)
	{
		FMyBeam newBeam(&newPoints[n], &newPoints[n + 1]);
		newBeams.Add(newBeam);
	}

}

void Pattern::SpawnNextStep(const UObject* world)
{
	for (int32 n = 0; n < newPoints.Num(); n++)
	{
		if (!newPoints[n].IsSpawned)
		{
			newPoints[n].SpawnPoint(world, mySparker);
			break;
		}
	}

	for (int32 n = 0; n < newBeams.Num(); n++)
	{
		if (!newBeams[n].IsSpawned)
		{
			newBeams[n].SpawnBeam(world, myBeam);
			break;
		}
	}

}
