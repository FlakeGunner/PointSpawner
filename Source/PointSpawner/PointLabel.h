// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PointLabel.generated.h"

UCLASS()
class POINTSPAWNER_API APointLabel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointLabel();
	//True for Visible, False for hidden
	void SetVisibilityOfPoint(bool Visibility);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UTextRenderComponent* m_PointLabel;
	
};
