// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/ASAttribute.h"
#include "Net/UnrealNetwork.h"

void UASAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UASAttribute, BaseValue);
	DOREPLIFETIME(UASAttribute, CurrentValue);
}

bool UASAttribute::AddModifier(TSubclassOf<UASAttributeModifier> ModifierClass)
{
	if(!ensure(ModifierClass)) return false;

	auto* NewModifier = NewObject<UASAttributeModifier>(this, ModifierClass);
	if(!ensure(NewModifier)) return false;

	Modifiers.Add(NewModifier->GetGameplayTag(), NewModifier);

	switch (NewModifier->GetOperation())
	{
		case EModifierOperation::Add :
			SetCurrentValue(GetCurrentValue() + NewModifier->ModifierValue);
			break;
		case EModifierOperation::Subtract :
			SetCurrentValue(GetCurrentValue() - NewModifier->ModifierValue);
			break;
		case EModifierOperation::Multiply :
			SetCurrentValue(GetCurrentValue() * NewModifier->ModifierValue);
			break;
		case EModifierOperation::Divide :
			SetCurrentValue(GetCurrentValue() / NewModifier->ModifierValue);
			break;
	}
	
	return true;
}

bool UASAttribute::RemoveModifier(FGameplayTag ModifierTag)
{
	const auto* PMod = Modifiers.Find(ModifierTag);
	if(PMod == nullptr) return false;
	Modifiers.Remove(ModifierTag);

	auto Modifier = *PMod;
	switch (Modifier->GetOperation())
	{
	case EModifierOperation::Add :
		SetCurrentValue(GetCurrentValue() - Modifier->ModifierValue);
		break;
	case EModifierOperation::Subtract :
		SetCurrentValue(GetCurrentValue() + Modifier->ModifierValue);
		break;
	case EModifierOperation::Multiply :
		SetCurrentValue(GetCurrentValue() / Modifier->ModifierValue);
		break;
	case EModifierOperation::Divide :
		SetCurrentValue(GetCurrentValue() * Modifier->ModifierValue);
		break;
	}
	
	return true;
}

void UASAttribute::OnRep_BaseValue(float OldValue)
{
	BaseValueChanged.Broadcast(OldValue, BaseValue);
}

void UASAttribute::OnRep_CurrentValue(float OldValue)
{
	UE_LOG(LogTemp, Log, TEXT("BRODCASTIN THE EVENT on current value changed"));
	CurrentValueChanged.Broadcast(OldValue, CurrentValue);
}
