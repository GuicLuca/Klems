﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAbilityComponent.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "ASAbility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ABILITYSYSTEM_API UASAbility : public UObject
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override {return true;};
	
	UFUNCTION(BlueprintNativeEvent, Category="Ability")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category="Ability")
	bool Start(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category="Ability")
	bool CanStop(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Ability")
	bool Stop(AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category="Ability")
	bool IsRunning() const { return bRunning; }

	UFUNCTION(BlueprintCallable, Category="Ability")
	FGameplayTagContainer IsBlockedBy(AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category="Ability")
	FGameplayTag GetGameplayTag() const { return AbilityTag; }

	UPROPERTY(EditDefaultsOnly, Category="Ability")
	bool bAutoStart;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	FName AbilityName;

	UPROPERTY(EditDefaultsOnly, Category="Ability")
	FGameplayTag AbilityTag;

	UPROPERTY(EditDefaultsOnly, Category="Tag")
	FGameplayTagContainer GrantedTags;

	UPROPERTY(EditDefaultsOnly, Category="Tag")
	FGameplayTagContainer BlockedTags;

	// Override the getWorld to get the method from the outer object
	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, Category="Ability")
	UASAbilityComponent* GetOwningComponent() const;
private:
	bool bRunning = false;
};
