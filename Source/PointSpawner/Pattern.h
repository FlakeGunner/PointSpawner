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

	virtual void SpawnNextStep(const UObject* world) = 0;

	virtual void TeardownPattern() = 0;

protected:

	TArray<FMyPoint> m_Points;
	
	TArray<FMyBeam> m_Beams;
	
	UParticleSystem* m_Sparker;
	
	UParticleSystem* m_Beam;

	int32 m_NumberOfPoints; 

	EPlotDirection m_Direction;
};
