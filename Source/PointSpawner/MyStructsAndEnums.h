// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "MyStructsAndEnums.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EPlotDirection : uint8
{
	UP 		UMETA(DisplayName = "Upwards"),
	DOWN 	UMETA(DisplayName = "Downwards"),
	RIGHT	UMETA(DisplayName = "Right"),
	LEFT	UMETA(DisplayName = "Left"),
	FORWARD	UMETA(DisplayName = "Forwards"),
	BACK	UMETA(DisplayName = "Backwards"),
	RANDOM	UMETA(DisplayName = "Random")
};


USTRUCT()
struct FMyPoint
{

	GENERATED_USTRUCT_BODY()

	FVector PointLocation;

	bool IsSpawned = false;

	UParticleSystemComponent* SparkPSC;

	FMyPoint() { }

	~FMyPoint()
	{
		SparkPSC = nullptr;
	}
	
	FMyPoint(FVector spawnLocation)
	{
		PointLocation = spawnLocation;
	}

	bool SpawnPoint(const UObject* world, UParticleSystem* myParticleSystem)
	{
		check(!PointLocation.ContainsNaN());

		SparkPSC = UGameplayStatics::SpawnEmitterAtLocation(world, myParticleSystem, PointLocation, FRotator(0.0f));

		if (SparkPSC)
		{
			SparkPSC->ActivateSystem();
			IsSpawned = true;
			return true;
		}
		else
		{
			return false;
		}
	}

	void Teardown()
	{
		
		SparkPSC->Deactivate();
		SparkPSC->DestroyComponent();
		
	}
};

USTRUCT()
struct FMyBeam
{

	GENERATED_USTRUCT_BODY()

	FMyPoint* StartPoint;

	FMyPoint* EndPoint;

	bool IsSpawned = false;

	UParticleSystemComponent* BeamPSC;

	FMyBeam() { }
	
	~FMyBeam() 
	{
		StartPoint = nullptr;
		EndPoint = nullptr;
		BeamPSC = nullptr;
	}

	FMyBeam(FMyPoint* spawnStartPoint, FMyPoint* spawnEndPoint)
	{
		StartPoint = spawnStartPoint;
		EndPoint = spawnEndPoint;
	}

	bool SpawnBeam(const UObject* world, UParticleSystem* myParticleSystem)
	{
		check(!StartPoint->PointLocation.ContainsNaN());
		check(!EndPoint->PointLocation.ContainsNaN());

		BeamPSC = UGameplayStatics::SpawnEmitterAtLocation(world, myParticleSystem, StartPoint->PointLocation, FRotator(0.0f));
		if (BeamPSC)
		{
			BeamPSC->ActivateSystem(true);
			BeamPSC->SetBeamSourcePoint(0, StartPoint->PointLocation, 0);
			BeamPSC->SetBeamTargetPoint(0, EndPoint->PointLocation, 0);
			IsSpawned = true;
			return true;
		}
		else
		{
			return false;
		}
	}

	void Teardown()
	{
		
		BeamPSC->Deactivate();
		BeamPSC->DestroyComponent();
		StartPoint = nullptr;
		EndPoint = nullptr;
		BeamPSC = nullptr;
		
	}
};