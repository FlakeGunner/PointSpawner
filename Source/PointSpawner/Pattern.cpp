// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "Pattern.h"


Pattern::Pattern()
{
	m_ShowPointLocations = false;
}

Pattern::~Pattern()
{
	m_Sparker = nullptr;
	m_Beam = nullptr;
	m_Points.Empty();
	m_Beams.Empty();
}

void Pattern::InitParticleSystems(UParticleSystem* Sparker, UParticleSystem* Beam)
{
	m_Sparker = Sparker;
	m_Beam = Beam;
}

void Pattern::SpawnNextStep(UWorld* world)
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
		if (CurBeam.IsSpawned)
		{
			CurBeam.Teardown();
		}
	}

	for (auto& CurPoint : m_Points)
	{
		if (CurPoint.IsSpawned)
		{
			CurPoint.Teardown();
		}
	}
	m_Sparker = nullptr;
	m_Beam = nullptr;
	m_Points.Empty();
	m_Beams.Empty();
}

void Pattern::TogglePointLocations()
{
	if (m_ShowPointLocations)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hide Point Locations"));
		for (auto& CurPoint : m_Points)
		{
			CurPoint.ToggleVisibility(false);
		}
		
		m_ShowPointLocations = false;

		
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Show Point Locations"));
		for (auto& CurPoint : m_Points)
		{
			CurPoint.ToggleVisibility(true);
		}
		m_ShowPointLocations = true;
	}
}