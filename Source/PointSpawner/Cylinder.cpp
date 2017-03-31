// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "Cylinder.h"

Cylinder::Cylinder(int32 NumberOfPoints, int32 Layers, float Radius)
{

	m_NumberOfPoints = NumberOfPoints;
		
	m_Layers = Layers; 
	
	m_Radius = Radius;

}

void Cylinder::GeneratePattern()
{
	float generatedX, generatedY, generatedZ, currentDegree;

	generatedX = generatedZ = generatedY = currentDegree = 0;

	for (int32 currentLayer = 0; currentLayer < m_Layers; currentLayer++)
	{
		for (int32 n = 0; n < m_NumberOfPoints; n++)
		{
			currentDegree = n * (360 / m_NumberOfPoints);

			generatedX = m_Radius * (FMath::Cos(FMath::DegreesToRadians(currentDegree)));

			generatedY = m_Radius * (FMath::Sin(FMath::DegreesToRadians(currentDegree)));

			generatedZ = (float)currentLayer * 50.0f;

			FVector newRandomLocation(generatedX, generatedY, generatedZ);
			FMyPoint newPoint(newRandomLocation);
			m_Points.Add(newPoint);
		}
	}

	for (int32 n = 0; n < m_Points.Num() - 1; n++)
	{
		FMyBeam newBeam(&m_Points[n], &m_Points[n + 1]);
		m_Beams.Add(newBeam);
	}
}

int32 Cylinder::GetNumberOfPoints()
{
	return m_Points.Num();
}