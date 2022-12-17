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
}
void UKSCombatComponent::Fire()
{
	Ammo--;
	OnFireDelegate.Broadcast();
}


void UKSCombatComponent::Reload()
{
	Ammo=10;
	OnReloadDelegate.Broadcast();

}

void UKSCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UKSCombatComponent::EquipWeapon(AKSWeapon* Weapon)
{
	{
		if(!ensure(Character)) return;
		if(!Weapon) return;
		//if(!Character->HasAuthority()) return;

		EquippedWeapon = Weapon;
		const auto* HandSocket = Character->GetMesh()->GetSocketByName(WeaponSocketName);
		if(!ensure(HandSocket)) return;
	
		//Attaching is always replicated by Unreal so no need to replicate
		EquippedWeapon->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		HandSocket->AttachActor(EquippedWeapon, Character->GetMesh());
		EquippedWeapon->SetActorRelativeLocation(FVector::Zero());
		//By default actor does not have owner since we are equipping it we are its owner
		EquippedWeapon->SetOwner(Character);
	}
}



