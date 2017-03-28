// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "PointSpawnerPlayerController.h"

void APointSpawnerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
