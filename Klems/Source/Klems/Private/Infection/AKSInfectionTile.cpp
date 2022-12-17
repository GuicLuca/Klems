// Fill out your copyright notice in the Description page of Project Settings.


#include "Klems/Public/Infection/AKSInfectionTile.h"


// Sets default values
AAKSInfectionTile::AAKSInfectionTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AAKSInfectionTile::Infect_Implementation(float InfectAmount)
{
	if(!TileDynamicMat) return;

	float InfectionDensity;
	TileDynamicMat->GetScalarParameterValue(FHashedMaterialParameterInfo("InfectionDensity"),InfectionDensity);

	//if(!ensureMsgf(InfectionDensity, "Material Instance do not have any scalar parameter %s")) return;
	
	TileDynamicMat->
}

// Called when the game starts or when spawned
void AAKSInfectionTile::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInterface* objectMaterial = this->Tile->GetMaterial(0);

	this->TileDynamicMat = UMaterialInstanceDynamic::Create(objectMaterial, Tile);
}


