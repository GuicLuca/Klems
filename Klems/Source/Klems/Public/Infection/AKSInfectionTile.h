// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AKSInfectionTile.generated.h"

UCLASS()
class KLEMS_API AKSInfectionTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKSInfectionTile();

	UFUNCTION(BlueprintNativeEvent)
	void Infect(float InfectAmount);

	UMaterialInstanceDynamic* TileDynamicMat = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UStaticMesh* Tile;
};
