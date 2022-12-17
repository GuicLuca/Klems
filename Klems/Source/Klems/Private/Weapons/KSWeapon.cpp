// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/KSWeapon.h"

#include "Net/UnrealNetwork.h"


AKSWeapon::AKSWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));

}

void AKSWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AKSWeapon,Ammo);
}

void AKSWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AKSWeapon::Reload_Implementation()
{
}

void AKSWeapon::Fire_Implementation()
{
}



