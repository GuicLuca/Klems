// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/KSWeapon.h"

#include "Net/UnrealNetwork.h"


AKSWeapon::AKSWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));

}



void AKSWeapon::BeginPlay()
{
	Super::BeginPlay();
}





