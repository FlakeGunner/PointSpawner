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
