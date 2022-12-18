// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KSCharacter.h"
#include "Components/ActorComponent.h"
#include "Weapons/KSWeapon.h"
#include "KSCombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHit);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KLEMS_API UKSCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKSCombatComponent();
	UFUNCTION(BlueprintCallable)
	void Init(AKSCharacter* character) {Character = character;}


	
	
	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AKSWeapon* Weapon,AKSWeapon* WeaponFPS);
	
	UFUNCTION(BlueprintCallable)
	void DecrementAmmo(int32 AmmoNumber);

	UFUNCTION(BlueprintCallable)
	void DecrementHealth(int32 amount);

	UFUNCTION(BlueprintCallable)
	bool CanShoot();

	UFUNCTION()
	void OnRep_OnAmmoChanged();

	UFUNCTION()
	void OnRep_OnHealthChanged();
	
	UPROPERTY(BlueprintCallable)
	FOnFire OnFireDelegate;
	
	UPROPERTY(BlueprintCallable)
	FOnReload OnReloadDelegate;

	UPROPERTY(BlueprintCallable)
	FOnHit OnHitDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	AKSWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere)
	AKSWeapon* EquippedWeaponFPS;
	
	UPROPERTY(EditDefaultsOnly)
	FName WeaponSocketName;
	
	UPROPERTY()
	AKSCharacter* Character;

	
	UPROPERTY(Replicated,BlueprintReadWrite,ReplicatedUsing=OnRep_OnAmmoChanged)
	int32 Ammo;

	UPROPERTY(Replicated,BlueprintReadWrite,ReplicatedUsing=OnRep_OnHealthChanged)
	int32 Health = 100;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxHealth;


};
