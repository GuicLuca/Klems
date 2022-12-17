// Fill out your copyright notice in the Description page of Project Settings.


#include "Klems/Public/Infection/KSInfectionTile.h"

#include "IContentBrowserSingleton.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AKSInfectionTile::AKSInfectionTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	Tile->SetupAttachment(RootComponent);
}

void AKSInfectionTile::addInfectionDensity(float newValue)
{
	if(!HasAuthority()) return;

	if(InfectionDensity >= 1) return;

	this->InfectionDensity = this->InfectionDensity+newValue;

	SetInfection(InfectionDensity);
}

void AKSInfectionTile::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	DOREPLIFETIME( AKSInfectionTile, InfectionDensity );
}

void AKSInfectionTile::SetInfection(float InfectDensity)
{
	
	if(!TileDynamicMat) return;

	TileDynamicMat->SetScalarParameterValue(FName("InfectionDensity"),InfectDensity);
	
}

void AKSInfectionTile::OnRep_InfectionDensity(float LastInfectionDensity)
{
	SetInfection(InfectionDensity);
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


