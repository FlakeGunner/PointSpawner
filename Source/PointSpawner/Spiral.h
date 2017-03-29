// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/KismetMathLibrary.h"
#include "Pattern.h"
/**
 * 
 */
class POINTSPAWNER_API Spiral: public Pattern
{
public:
	Spiral(int32 NumberOfPoints);

	void GeneratePattern();
};
