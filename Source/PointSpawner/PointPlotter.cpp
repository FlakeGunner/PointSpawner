// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "PointPlotter.h"



// Sets default values
APointPlotter::APointPlotter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> locateSparker(TEXT("ParticleSystem'/Game/P_Sparker.P_Sparker'"));
	if (&locateSparker != nullptr)
	{
		m_Sparker = locateSparker.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> locateBeam(TEXT("ParticleSystem'/Game/P_Beam.P_Beam'"));
	if (&locateBeam != nullptr)
	{
		m_Beam = locateBeam.Object;
	}
}

// Called when the game starts or when spawned
void APointPlotter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APointPlotter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APointPlotter::AdvanceTimer()
{
	--m_CurrentTime;
	m_RandomPath->SpawnNextStep(GetWorld());
	if (m_CurrentTime < 1)
	{
		//We're done counting down, so stop running the timer.
		GetWorldTimerManager().ClearTimer(m_SpawnTimerHandle);
		SpawnTimerHasFinished();
	}
	
}

void APointPlotter::SpawnTimerHasFinished()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Timer Finished!"));
}

void APointPlotter::PlotPattern(Pattern* PatternToPlot)
{
	m_RandomPath = PatternToPlot;

	m_RandomPath->InitParticleSystems(m_Sparker, m_Beam);

	m_RandomPath->GeneratePattern();

	//must be called after generate pattern
	m_CurrentTime = PatternToPlot->GetNumberOfPoints();

	GetWorldTimerManager().SetTimer(m_SpawnTimerHandle, this, &APointPlotter::AdvanceTimer, 0.3f, true);
}

void APointPlotter::TeardownPattern()
{
	GetWorldTimerManager().ClearTimer(m_SpawnTimerHandle);
	m_RandomPath->TeardownPattern();
}

