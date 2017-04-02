// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "SpherePattern.h"

SpherePattern::SpherePattern(int32 NumberOfPoints, float Radius)
{
	m_Radius = Radius;
	m_NumberOfPoints = NumberOfPoints;
	m_NumberOfLayers = 12;
}

int32 SpherePattern::GetNumberOfPoints()
{
	return m_Points.Num();
}

void SpherePattern::GeneratePattern()
{
	float currentLatitude = 0.0f;
	float currentLongitude = 0.0f;
		
	for (int32 outer = 0; outer < (m_NumberOfLayers / 2); outer++)
	{
		currentLongitude = outer * (360 / m_NumberOfLayers);

		for (int32 inner = 0; inner < m_NumberOfPoints; inner++)
		{
			currentLatitude = inner * (360 / m_NumberOfPoints);
			FVector currentVector = LatitudeLongitudeToCartesian(m_Radius, currentLatitude, currentLongitude);
			FMyPoint newPoint(currentVector);
			m_Points.Add(newPoint);
		}
		
	}

	for (int32 outer = 0; outer < (m_NumberOfLayers / 2); outer++)
	{
		int32 beamStart = outer * m_NumberOfPoints;
		int32 beamEnd = ((outer * m_NumberOfPoints) + m_NumberOfPoints) - 1;

		for (int32 inner = 0; inner < m_NumberOfPoints - 1; inner++)
		{
			FMyBeam newBeam(&m_Points[beamStart + inner], &m_Points[beamStart + inner + 1]);
			m_Beams.Add(newBeam);

			if (inner == m_NumberOfPoints - 2)
			{
				FMyBeam newBeam(&m_Points[beamStart], &m_Points[beamStart + inner + 1]);
				m_Beams.Add(newBeam);
			}
		}
	}
}

// Special thanks to https://vvvv.org/blog/polar-spherical-and-geographic-coordinates 
// and https://blog.nobel-joergensen.com/2010/10/22/spherical-coordinates-in-unity/
// for the math to make this conversion
FVector SpherePattern::LatitudeLongitudeToCartesian(float Radius, float Latitude, float Longitude)
{

	float X, Y, Z;

	float LatitudeInRadians = FMath::DegreesToRadians(Latitude);
	float LongitudeInRadians = FMath::DegreesToRadians(Longitude);

	X = Radius * FMath::Cos((LatitudeInRadians)) * FMath::Sin((LongitudeInRadians));
	Y = -Radius * FMath::Cos((LatitudeInRadians)) * FMath::Cos((LongitudeInRadians));
	Z = Radius * FMath::Sin((LatitudeInRadians));

	return FVector(X, Y, Z);

}