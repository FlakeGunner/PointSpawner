// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyStructsAndEnums.h"
/**
 * 
 */


class POINTSPAWNER_API Pattern
{
public:

	Pattern();
	
	~Pattern();

	virtual void GeneratePattern() = 0;

	void InitParticleSystems(UParticleSystem* Sparker, UParticleSystem* Beam);

	void SpawnNextStep(const UObject* world);

	void TeardownPattern();

	int32 m_NumberOfPoints;

protected:

	TArray<FMyPoint> m_Points;
	
	TArray<FMyBeam> m_Beams;
	
	UParticleSystem* m_Sparker;
	
	UParticleSystem* m_Beam;
};
