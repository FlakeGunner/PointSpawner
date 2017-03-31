// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/KismetMathLibrary.h"
#include "Pattern.h"

/**
 * 
 */
class POINTSPAWNER_API Cylinder: public Pattern
{
public:
	Cylinder(int32 NumberOfPoints, int32 Layers, float Radius);

	void GeneratePattern();

	int32 GetNumberOfPoints();

protected:

	int32 m_NumberOfPoints;
	int32 m_Layers;
	float m_Radius;
};
