// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AKSInfectionTile.generated.h"

UCLASS(Blueprintable)
class KLEMS_API AKSInfectionTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKSInfectionTile();

	UFUNCTION(BlueprintCallable)
	void Infect(float InfectAmount);

	UFUNCTION(BlueprintCallable)
	void SetInfection(float InfectDensity = 0);

	UPROPERTY(BlueprintReadWrite, Category = "Material")
	UMaterialInstanceDynamic* TileDynamicMat = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> Tile;
};
