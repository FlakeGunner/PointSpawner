// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PointPlotter.generated.h"

USTRUCT()
struct FMyPoint
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		FVector PointLocation;

	UPROPERTY(EditAnywhere)
		bool IsSpawned = false;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* SparkPSC;

	FMyPoint() { }

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
};

USTRUCT()
struct FMyBeam
{

	GENERATED_USTRUCT_BODY()

	FMyPoint* StartPoint;

	FMyPoint* EndPoint;

	UPROPERTY(EditAnywhere)
		bool IsSpawned = false;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* BeamPSC;

	FMyBeam() { }

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
};

UCLASS()
class POINTSPAWNER_API APointPlotter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointPlotter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// called by timer to spawn next point
	void SpawnNextPoint();

	void SpawnNextBeam();

	void AdvanceTimer();

	void SpawnTimerHasFinished();

	FTimerHandle SpawnTimerHandle;

	int32 CurrentTime;

	TArray<FMyPoint> newPoints;
	
	TArray<FMyBeam> newBeams;

	UPROPERTY(EditAnywhere)
		UParticleSystem* mySparker;
	UPROPERTY(EditAnywhere)
		UParticleSystem* myBeam;
	UPROPERTY(EditAnywhere)
		int32 NumberOfPoints = 20;
	

};


