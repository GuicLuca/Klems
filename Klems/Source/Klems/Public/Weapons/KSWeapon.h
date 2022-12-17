// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/ASAbilityComponent.h"
#include "GameFramework/Actor.h"
#include "KSWeapon.generated.h"

class AKSCharacter;
UCLASS()
class KLEMS_API AKSWeapon : public AActor
{
	GENERATED_BODY()

public:
	AKSWeapon();

protected:
	virtual void BeginPlay() override;
	

	
	
	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	

	

	
	

};
