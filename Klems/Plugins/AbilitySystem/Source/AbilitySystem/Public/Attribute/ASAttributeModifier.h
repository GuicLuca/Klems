// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "ASAttributeModifier.generated.h"


UENUM(BlueprintType)
enum class EModifierOperation : uint8
{
	Add,
	Multiply,
	Divide,
	Subtract
};

UCLASS(BlueprintType,Blueprintable)
class ABILITYSYSTEM_API UASAttributeModifier : public UObject
{
public:
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="Attribute Modifier")
	FORCEINLINE FGameplayTag GetGameplayTag() const { return Tag; }

	UFUNCTION(BlueprintCallable, Category="Attribute Modifier")
	FORCEINLINE EModifierOperation GetOperation() const { return ModifierOperation; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute Modifier")
	float ModifierValue;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attribute Modifier", meta=(AllowPrivateAccess=true))
	FName Name;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attribute Modifier", meta=(AllowPrivateAccess=true))
	FGameplayTag Tag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attribute Modifier", meta=(AllowPrivateAccess=true))
	EModifierOperation ModifierOperation;
};
