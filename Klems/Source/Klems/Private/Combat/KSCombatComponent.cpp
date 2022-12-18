// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/KSCombatComponent.h"



#include "Engine/SkeletalMeshSocket.h"
#include "Net/UnrealNetwork.h"


UKSCombatComponent::UKSCombatComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}
void UKSCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UKSCombatComponent,Ammo);
	//DOREPLIFETIME(UKSCombatComponent,Health);
}


void UKSCombatComponent::Reload()
{
	Ammo=-1;
	OnReloadDelegate.Broadcast();
}

void UKSCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UKSCombatComponent::EquipWeapon(AKSWeapon* Weapon,AKSWeapon* WeaponFPS)
{
	{
		if(!ensure(Character)) return;
		if(!Weapon) return;
		if(!WeaponFPS) return;
		//if(!Character->HasAuthority()) return;

		EquippedWeapon = Weapon;
		const auto* HandSocket = Character->GetMesh()->GetSocketByName(WeaponSocketName);
		if(!ensure(HandSocket)) return;
	
		//Attaching is always replicated by Unreal so no need to replicate
		EquippedWeapon->SetActorRotation(FRotator(90.0f, 90.0f, 90.0f));
		HandSocket->AttachActor(EquippedWeapon, Character->GetMesh());
		//EquippedWeapon->SetActorRelativeLocation(FVector::Zero());
		//By default actor does not have owner since we are equipping it we are its owner
		EquippedWeapon->SetOwner(Character);

		EquippedWeaponFPS = WeaponFPS;
		const auto* HandSocketFPS = Character->GetFPSMesh()->GetSocketByName(WeaponSocketName);
		if(!ensure(HandSocketFPS)) return;
	
		//Attaching is always replicated by Unreal so no need to replicate
		EquippedWeaponFPS->SetActorRotation(FRotator(90.0f, 90.0f, 90.0f));
		HandSocketFPS->AttachActor(EquippedWeaponFPS, Character->GetFPSMesh());
		//EquippedWeapon->SetActorRelativeLocation(FVector::Zero());
		//By default actor does not have owner since we are equipping it we are its owner
		EquippedWeaponFPS->SetOwner(Character);

		Ammo = MaxAmmo;
		//Health = MaxHealth;
	}
}

void UKSCombatComponent::DecrementAmmo(int32 AmmoNumber)
{
	
	if(Ammo-AmmoNumber < 0) return;
	OnFireDelegate.Broadcast();
	Ammo--;
}

bool UKSCombatComponent::CanShoot()
{
	return (Ammo > 0);
}

void UKSCombatComponent::OnRep_OnAmmoChanged()
{
	if(!Character) return;
	Character->OnAmmoChanged(0,Ammo);
}



void UKSCombatComponent::Die_Implementation()
{
}



