// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KSCharacter.h"
#include "Components/ActorComponent.h"
#include "Weapons/KSWeapon.h"
#include "KSCombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KLEMS_API UKSCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKSCombatComponent();
	UFUNCTION(BlueprintCallable)
	void Init(AKSCharacter* character) {Character = character;}

	UFUNCTION(BlueprintNativeEvent)
	void Fire();

	UFUNCTION(BlueprintNativeEvent)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AKSWeapon* Weapon);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	AKSWeapon* EquippedWeapon;
	
	UPROPERTY(EditDefaultsOnly)
	FName WeaponSocketName;
	
	UPROPERTY()
	AKSCharacter* Character;

	UPROPERTY(Replicated,BlueprintReadWrite)
	int32 Ammo;

public:

};
