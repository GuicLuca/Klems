// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAttribute.h"
#include "Components/ActorComponent.h"
#include "ASAttributeSetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ABILITYSYSTEM_API UASAttributeSetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UASAttributeSetComponent();

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UFUNCTION(BlueprintCallable)
	UASAttribute* GetAttribute(FGameplayTag Tag);

	const UASAttribute* GetAttribute(FGameplayTag Tag) const;

	UFUNCTION(BlueprintCallable)
	bool GetAttributeBase(FGameplayTag Tag, float& OutValue) const;

	UFUNCTION(BlueprintCallable)
	bool GetAttributeCurrent(FGameplayTag Tag, float& OutValue) const;

	UFUNCTION(BlueprintCallable)
	void AddAttribute(TSubclassOf<UASAttribute> AttributeClass);

	UFUNCTION(BlueprintCallable)
	void RemoveAttribute(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	bool AddToCurrentValue(FGameplayTag Tag, float Value, float& NewValue);

	UFUNCTION(BlueprintCallable)
	bool AddToBaseValue(FGameplayTag Tag, float Value, float& NewValue);

	UFUNCTION(BlueprintCallable)
	bool SubstractToCurrentValue(FGameplayTag Tag, float Value, float& NewValue);

	UFUNCTION(BlueprintCallable)
	bool SubstractToBaseValue(FGameplayTag Tag, float Value, float& NewValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attribute")
	TArray<TSubclassOf<UASAttribute>> DefaultAttributes;

	UFUNCTION(BlueprintCallable)
	bool AddModifier(FGameplayTag AttributeTag, TSubclassOf<UASAttributeModifier> ModifierClass);

	UFUNCTION(BlueprintCallable)
	bool RemoveModifier(FGameplayTag AttributeTag, FGameplayTag ModifierTag);

	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<UASAttribute*> Attributes;

};
