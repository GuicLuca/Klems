// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KSInfectionTile.generated.h"

UCLASS(Blueprintable)
class KLEMS_API AKSInfectionTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKSInfectionTile();

	UFUNCTION(BlueprintCallable)
	void addInfectionDensity(float newValue);
	
	UFUNCTION()
	void OnRep_InfectionDensity(float LastInfectionDensity);

	UPROPERTY(BlueprintReadWrite, Category = "Material")
	UMaterialInstanceDynamic* TileDynamicMat = nullptr;

	UPROPERTY(Replicated, ReplicatedUsing=OnRep_InfectionDensity)
	float InfectionDensity = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void SetInfection(float InfectDensity = 0);

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> Tile;
};
