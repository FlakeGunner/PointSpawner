// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "RandomPath.h"

RandomPath::RandomPath(int32 NumberOfPoints, EPlotDirection Direction)
{
	m_NumberOfPoints = NumberOfPoints;
	m_Direction = Direction;
}

int32 RandomPath::GetNumberOfPoints()
{
	return m_NumberOfPoints;
}

void RandomPath::GeneratePattern()
{
	float generatedX, generatedY, generatedZ, randomRange;

	generatedX = generatedZ = generatedY = 0;

	randomRange = 80.0f;

	for (int32 n = 0; n < m_NumberOfPoints; n++)
	{

		if (m_Direction == EPlotDirection::UP)
		{
			generatedX = FMath::RandRange(-randomRange, randomRange);
			generatedY = FMath::RandRange(-randomRange, randomRange);
			generatedZ += FMath::RandRange((randomRange / 2), randomRange);
		}
		else if (m_Direction == EPlotDirection::DOWN)
		{
			generatedX = FMath::RandRange(-randomRange, randomRange);
			generatedY = FMath::RandRange(-randomRange, randomRange);
			generatedZ += FMath::RandRange(-(randomRange / 2), -randomRange);

		}
		else if (m_Direction == EPlotDirection::RIGHT)
		{
			generatedX = FMath::RandRange(-randomRange, randomRange);
			generatedY += FMath::RandRange((randomRange / 2), randomRange);
			generatedZ = FMath::RandRange(-randomRange, randomRange);

		}
		else if (m_Direction == EPlotDirection::LEFT)
		{
			generatedX = FMath::RandRange(-randomRange, randomRange);
			generatedY += FMath::RandRange(-(randomRange / 2), -randomRange);
			generatedZ = FMath::RandRange(-randomRange, randomRange);

		}
		else if (m_Direction == EPlotDirection::FORWARD)
		{
			generatedX += FMath::RandRange((randomRange / 2), randomRange);
			generatedY = FMath::RandRange(-randomRange, randomRange);
			generatedZ = FMath::RandRange(-randomRange, randomRange);

		}
		else if (m_Direction == EPlotDirection::BACK)
		{
			generatedX += FMath::RandRange(-(randomRange / 2), -randomRange);
			generatedY = FMath::RandRange(-randomRange, randomRange);
			generatedZ = FMath::RandRange(-randomRange, randomRange);
		}
		else if (m_Direction == EPlotDirection::RANDOM)
		{
			generatedX = FMath::RandRange(-(randomRange * 3), (randomRange * 3));
			generatedY = FMath::RandRange(-(randomRange * 3), (randomRange * 3));
			generatedZ = FMath::RandRange(-(randomRange * 3), (randomRange * 3));
		}
		else
		{
			generatedX = 10 * n;
			generatedY = 10 * n;
			generatedZ = 10 * n;
		}

		FVector newRandomLocation(generatedX, generatedY, generatedZ);
		FMyPoint newPoint(newRandomLocation);
		m_Points.Add(newPoint);

	}

	for (int32 n = 0; n < m_Points.Num() - 1; n++)
	{
		FMyBeam newBeam(&m_Points[n], &m_Points[n + 1]);
		m_Beams.Add(newBeam);
	}
}



