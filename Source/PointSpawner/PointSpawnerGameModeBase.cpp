// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
#include "Pattern.h"
#include "RandomPath.h"
#include "Spiral.h"
#include "PointSpawnerGameModeBase.h"

void APointSpawnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}


void APointSpawnerGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void APointSpawnerGameModeBase::PlotDirection(EPlotDirection Direction)
{
	UWorld* World = GetWorld();
	
	if (World != nullptr)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController != nullptr)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameAndUI());

			FVector Location(0.0f, 0.0f, 0.0f);
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnInfo;
			m_PointPlotter = World->SpawnActor<APointPlotter>(Location, Rotation, SpawnInfo);
			Pattern* RandomPathPattern = new RandomPath(32, Direction);
			m_PointPlotter->PlotPattern(RandomPathPattern);

		}
	}
}

void APointSpawnerGameModeBase::PlotSpiral()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController != nullptr)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameAndUI());

			FVector Location(0.0f, 0.0f, 0.0f);
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnInfo;
			m_PointPlotter = World->SpawnActor<APointPlotter>(Location, Rotation, SpawnInfo);
			Pattern* RandomPathPattern = new Spiral(32);
			m_PointPlotter->PlotPattern(RandomPathPattern);

		}
	}
}