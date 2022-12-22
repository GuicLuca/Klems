// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/KSWeapon.h"

#include "Net/UnrealNetwork.h"


AKSWeapon::AKSWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}



void AKSWeapon::BeginPlay()
{
	Super::BeginPlay();
}





