// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "PointLabel.h"


// Sets default values
APointLabel::APointLabel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_PointLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Point Label"));
}

// Called when the game starts or when spawned
void APointLabel::BeginPlay()
{
	Super::BeginPlay();

	m_PointLabel->SetHorizontalAlignment(EHTA_Right);
	m_PointLabel->SetWorldSize(10.0f);
	m_PointLabel->SetText(GetActorLocation().ToString());
}

// Called every frame
void APointLabel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

