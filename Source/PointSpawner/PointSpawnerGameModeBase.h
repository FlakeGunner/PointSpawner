// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyStructsAndEnums.h"
#include "PointPlotter.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Pattern.h"
#include "RandomPath.h"
#include "Spiral.h"
#include "SpherePattern.h"
#include "Cylinder.h"
#include "PointSpawnerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class POINTSPAWNER_API APointSpawnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Point Spawner")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	UFUNCTION(BlueprintCallable, Category = "Point Spawner")
		void PlotDirection(EPlotDirection Direction);
	UFUNCTION(BlueprintCallable, Category = "Point Spawner")
		void PlotSpiral();
	UFUNCTION(BlueprintCallable, Category = "Point Spawner")
		void PlotSphere();
	UFUNCTION(BlueprintCallable, Category = "Point Spawner")
		void PlotCylinder();
	UFUNCTION(BlueprintCallable, Category = "Point Spawner")
		void ReturnToMenu();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Point Spawner")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	APointPlotter* m_PointPlotter;

private:
	void ApplyPattern(Pattern* PatternToPlot);
};
