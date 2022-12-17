// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAttributeModifier.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "ASAttribute.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeBaseValueChangedDelegate,
	float, OldValue,
	float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeCurrentValueChangedDelegate,
	float, OldValue,
	float, NewValue);

UCLASS(Blueprintable)
class ABILITYSYSTEM_API UASAttribute : public UObject
{
	GENERATED_BODY()
public:
	virtual bool IsSupportedForNetworking() const override {return true;};

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, Category="Attribute")
	FORCEINLINE float GetBaseValue() const { return BaseValue; }

	UFUNCTION(BlueprintCallable, Category="Attribute")
	FORCEINLINE float SetBaseValue(float NewBaseValue)
	{
		BaseValueChanged.Broadcast(BaseValue, NewBaseValue);
		return BaseValue = NewBaseValue;
	}
	
	UFUNCTION(BlueprintCallable, Category="Attribute")
	FORCEINLINE float GetCurrentValue() const { return CurrentValue; }

	UFUNCTION(BlueprintCallable, Category="Attribute")
	FORCEINLINE float SetCurrentValue(float NewCurrentValue)
	{
		CurrentValueChanged.Broadcast(CurrentValue, NewCurrentValue);
		return CurrentValue = NewCurrentValue;
	}

	UPROPERTY(BlueprintReadWrite, Category="Attribute")
	FAttributeBaseValueChangedDelegate BaseValueChanged;

	UPROPERTY(BlueprintReadWrite, Category="Attribute")
	FAttributeCurrentValueChangedDelegate CurrentValueChanged;

	UFUNCTION(BlueprintCallable, Category="Attribute")
	FORCEINLINE FGameplayTag GetGameplayTag() const { return Tag; }

	UFUNCTION(BlueprintCallable, Category="Attribute")
	bool AddModifier(TSubclassOf<UASAttributeModifier> ModifierClass);

	UFUNCTION(BlueprintCallable, Category="Attribute")
	bool RemoveModifier(FGameplayTag ModifierTag);
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	FGameplayTag Tag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attribute", meta=(AllowPrivateAccess=true))
	FName Name;

	UPROPERTY(ReplicatedUsing= OnRep_BaseValue, EditAnywhere, Category="Attribute")
	float BaseValue = 0;
	
	UPROPERTY(ReplicatedUsing= OnRep_CurrentValue, EditAnywhere, Category="Attribute")
	float CurrentValue = 0;

	UFUNCTION()
	void OnRep_BaseValue(float OldValue);

	UFUNCTION()
	void OnRep_CurrentValue(float OldValue);

	UPROPERTY()
	TMap<FGameplayTag, UASAttributeModifier*> Modifiers;
};
