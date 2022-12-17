// Fill out your copyright notice in the Description page of Project Settings.


#include "Klems/Public/Infection/AKSInfectionTile.h"

#include "IContentBrowserSingleton.h"


// Sets default values
AKSInfectionTile::AKSInfectionTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	Tile->SetupAttachment(RootComponent);
}

void AKSInfectionTile::Infect(float InfectAmount)
{
	if(!TileDynamicMat) return;

	float InfectionDensity;
	TileDynamicMat->GetScalarParameterValue(FHashedMaterialParameterInfo("InfectionDensity"),InfectionDensity);

	if(InfectionDensity>1)
		TileDynamicMat->SetScalarParameterValue(FName("InfectionDensity"),1);
	else
		TileDynamicMat->SetScalarParameterValue(FName("InfectionDensity"),InfectionDensity+InfectAmount);
}

void AKSInfectionTile::SetInfection(float InfectDensity)
{
	if(!TileDynamicMat) return;

	TileDynamicMat->SetScalarParameterValue(FName("InfectionDensity"),InfectDensity);
	
}

// Called when the game starts or when spawned
void AKSInfectionTile::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInterface* objectMaterial = this->Tile->GetMaterial(0);

	this->TileDynamicMat = UMaterialInstanceDynamic::Create(objectMaterial, Tile);

	this->Tile->SetMaterial(0,TileDynamicMat);

	SetInfection();
}


