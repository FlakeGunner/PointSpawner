// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PointSpawnerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class POINTSPAWNER_API APointSpawnerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	
};
