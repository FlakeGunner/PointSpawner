// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/KismetMathLibrary.h"
#include "Pattern.h"

/**
 * Had to call this spherepattern to avoid namespace conflict with engine
 */
class POINTSPAWNER_API SpherePattern: public Pattern
{
public:
	SpherePattern(int32 NumberOfPoints, float Radius);

	void GeneratePattern();

	int32 GetNumberOfPoints();
	
protected:
	float m_Radius;

	int32 m_NumberOfLayers;

	FVector LatitudeLongitudeToCartesian(float Radius, float Latitude, float Longitude);
};
