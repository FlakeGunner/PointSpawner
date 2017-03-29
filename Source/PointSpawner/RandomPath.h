// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pattern.h"
/**
 * 
 */
class POINTSPAWNER_API RandomPath: public Pattern
{
public:

	RandomPath(UParticleSystem* Sparker, UParticleSystem* Beam, int32 NumberOfPoints, EPlotDirection Direction);

	void GeneratePattern();

	void SpawnNextStep(const UObject* world);

	void TeardownPattern();
};
