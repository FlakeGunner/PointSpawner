// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pattern.h"
/**
 * 
 */
class POINTSPAWNER_API RandomPath: public Pattern
{
public:

	RandomPath(int32 NumberOfPoints, EPlotDirection Direction);

	void GeneratePattern();

	int32 GetNumberOfPoints();

protected:
	EPlotDirection m_Direction;
};
