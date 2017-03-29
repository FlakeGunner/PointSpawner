// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "Spiral.h"

Spiral::Spiral(int32 NumberOfPoints)
{
	m_NumberOfPoints = NumberOfPoints;
}

void Spiral::GeneratePattern()
{
	float generatedX, generatedY, generatedZ, radius;

	generatedX = generatedZ = generatedY = radius = 0;

	float currentDegree = 0.0f;

	for (int32 n = 0; n < m_NumberOfPoints; n++)
	{

		currentDegree = n * (360 / m_NumberOfPoints);

		generatedX = radius * (FMath::Cos(FMath::DegreesToRadians(currentDegree)));

		generatedY = radius * (FMath::Sin(FMath::DegreesToRadians(currentDegree)));

		generatedZ += 20;

		FVector newRandomLocation(generatedX, generatedY, generatedZ);
		FMyPoint newPoint(newRandomLocation);
		m_Points.Add(newPoint);

		radius += 30;
	}

	for (int32 n = 0; n < m_Points.Num() - 1; n++)
	{
		FMyBeam newBeam(&m_Points[n], &m_Points[n + 1]);
		m_Beams.Add(newBeam);
	}

}



