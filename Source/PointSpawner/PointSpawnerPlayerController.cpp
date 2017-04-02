// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "PointSpawnerPlayerController.h"

void APointSpawnerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

void APointSpawnerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("ReturnToMenu", IE_Released, this, &APointSpawnerPlayerController::ReturnToMenu);
	InputComponent->BindAction("TogglePointLocations", IE_Released, this, &APointSpawnerPlayerController::TogglePointLocations);
}

void APointSpawnerPlayerController::ReturnToMenu()
{
	if (GetWorld())
	{
		APointSpawnerGameModeBase* CurrentGameMode = Cast<APointSpawnerGameModeBase>(GetWorld()->GetAuthGameMode());
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		CurrentGameMode->ReturnToMenu();
	}
}

void APointSpawnerPlayerController::TogglePointLocations()
{
	if (GetWorld())
	{
		APointSpawnerGameModeBase* CurrentGameMode = Cast<APointSpawnerGameModeBase>(GetWorld()->GetAuthGameMode());
		CurrentGameMode->TogglePointLocations();
	}
}
