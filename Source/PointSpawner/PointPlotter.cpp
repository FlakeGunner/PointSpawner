// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "PointPlotter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APointPlotter::APointPlotter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> locateSparker(TEXT("ParticleSystem'/Game/P_Sparker.P_Sparker'"));
	mySparker = locateSparker.Object;
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> locateBeam(TEXT("ParticleSystem'/Game/P_Beam.P_Beam'"));
	myBeam = locateBeam.Object;
	
}

// Called when the game starts or when spawned
void APointPlotter::BeginPlay()
{
	Super::BeginPlay();

	CurrentTime = NumberOfPoints;

	for (int32 n = 0; n < NumberOfPoints; n++)
	{
		FVector newRandomLocation((n * FMath::RandRange(20.0f, 40.0f)), (n * FMath::RandRange(20.0f, 40.0f)), (n * FMath::RandRange(20.0f, 40.0f)));
		FMyPoint newPoint(newRandomLocation);
		newPoints.Add(newPoint);

	}

	for (int32 n = 0; n < newPoints.Num() - 1; n++)
	{
		FMyBeam newBeam(&newPoints[n], &newPoints[n + 1]);
		newBeams.Add(newBeam);
	}

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &APointPlotter::AdvanceTimer, 0.3f, true);
}

// Called every frame
void APointPlotter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APointPlotter::AdvanceTimer()
{
	--CurrentTime;
	SpawnNextPoint();
	SpawnNextBeam();
	if (CurrentTime < 1)
	{
		//We're done counting down, so stop running the timer.
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		SpawnTimerHasFinished();
	}
	
}

void APointPlotter::SpawnNextPoint()
{	
	for (int32 n = 0; n < newPoints.Num(); n++)
	{
		if (!newPoints[n].IsSpawned)
		{
			newPoints[n].SpawnPoint(GetWorld(), mySparker);
			break;
		}
	}
}

void APointPlotter::SpawnNextBeam()
{
	for (int32 n = 0; n < newBeams.Num(); n++)
	{
		if (!newBeams[n].IsSpawned)
		{
			newBeams[n].SpawnBeam(GetWorld(), myBeam);
			break;
		}
	}
}

void APointPlotter::SpawnTimerHasFinished()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Timer Finished!"));
}

