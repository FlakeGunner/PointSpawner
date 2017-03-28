// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "Pattern.h"
#include <cmath> 

Pattern::Pattern(UParticleSystem* Sparker, UParticleSystem* Beam, int32 NumberOfPoints, EPlotDirection Direction)
{
	m_Sparker = Sparker;
	m_Beam = Beam;
	m_NumberOfPoints = NumberOfPoints;
	m_Direction = Direction;
}

Pattern::Pattern()
{
}

Pattern::~Pattern()
{
	m_Sparker = nullptr;
	m_Beam = nullptr;
	m_Points.Empty();
	m_Beams.Empty();
}

void Pattern::GeneratePattern()
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
			generatedX = FMath::RandRange(-(randomRange*3), (randomRange * 3));
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

void Pattern::SpawnNextStep(const UObject* world)
{
	for (int32 n = 0; n < m_Points.Num(); n++)
	{
		if (!m_Points[n].IsSpawned)
		{
			m_Points[n].SpawnPoint(world, m_Sparker);
			break;
		}
	}

	for (int32 n = 0; n < m_Beams.Num(); n++)
	{
		if (!m_Beams[n].IsSpawned)
		{
			m_Beams[n].SpawnBeam(world, m_Beam);
			break;
		}
	}

}

void Pattern::TeardownPattern()
{
	for (auto& CurBeam : m_Beams)
	{
		CurBeam.Teardown();
	}

	for (auto& CurPoint : m_Points)
	{
		CurPoint.Teardown();
	}
	m_Sparker = nullptr;
	m_Beam = nullptr;
	m_Points.Empty();
	m_Beams.Empty();
	
}
