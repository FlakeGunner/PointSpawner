// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyStructsAndEnums.h"
/**
 * 
 */


class POINTSPAWNER_API Pattern
{
public:
	
	Pattern(UParticleSystem* Sparker, UParticleSystem* Beam, int32 NumberOfPoints, FVector Direction);

	Pattern();
	
	~Pattern();

	void GeneratePattern();

	void SpawnNextStep(const UObject* world);

private:

	TArray<FMyPoint> m_Points;
	
	TArray<FMyBeam> m_Beams;
	
	UParticleSystem* m_Sparker;
	
	UParticleSystem* m_Beam;

	int32 m_NumberOfPoints; 

	FVector m_Direction;
};
