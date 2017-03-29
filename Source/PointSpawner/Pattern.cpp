// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "Pattern.h"
#include <cmath> 

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

void Pattern::InitParticleSystems(UParticleSystem* Sparker, UParticleSystem* Beam)
{
	m_Sparker = Sparker;
	m_Beam = Beam;
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