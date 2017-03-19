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
	UParticleSystem* mySparker = locateSparker.Object;
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> locateBeam(TEXT("ParticleSystem'/Game/P_Beam.P_Beam'"));
	UParticleSystem* myBeam = locateBeam.Object;

	m_NumberOfPoints = 32;

	m_RandomPath = new Pattern(mySparker, myBeam, m_NumberOfPoints, -FVector::RightVector);
	
}

// Called when the game starts or when spawned
void APointPlotter::BeginPlay()
{
	Super::BeginPlay();

	m_CurrentTime = m_NumberOfPoints;

	m_RandomPath->GeneratePattern();

	GetWorldTimerManager().SetTimer(m_SpawnTimerHandle, this, &APointPlotter::AdvanceTimer, 0.3f, true);
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
