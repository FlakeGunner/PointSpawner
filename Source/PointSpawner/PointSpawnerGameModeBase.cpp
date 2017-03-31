// Fill out your copyright notice in the Description page of Project Settings.

#include "PointSpawner.h"
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
	ApplyPattern(new RandomPath(32, Direction));
}

void APointSpawnerGameModeBase::PlotSpiral()
{
	ApplyPattern(new Spiral(32));
}

void APointSpawnerGameModeBase::PlotSphere()
{
	ApplyPattern(new SpherePattern(36, 300));
}

void APointSpawnerGameModeBase::PlotCylinder()
{
	ApplyPattern(new Cylinder(24, 10, 300));
}

void APointSpawnerGameModeBase::ApplyPattern(Pattern* PatternToPlot)
{
	UWorld* World = GetWorld();

	if (World)
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
			
			m_PointPlotter->PlotPattern(PatternToPlot);

		}
	}
}

void APointSpawnerGameModeBase::ReturnToMenu()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("returning to menu in game mode"));

	m_PointPlotter->TeardownPattern();
	ChangeMenuWidget(StartingWidgetClass);

}