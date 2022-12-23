// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/ASAbilityEffect.h"

void UASAbilityEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{
}

UASAbilityEffect::UASAbilityEffect()
{
	bAutoStart = true;
}

bool UASAbilityEffect::Start_Implementation(AActor* Instigator)
{
	const bool bRet = Super::Start_Implementation(Instigator);
	const auto * World  = GetWorld();
	if(!World) return false;
	
	if (Duration > 0.0F)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "stop", Instigator);
		
		
	}

	if (Period > 0.0F)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "ExecutePeriodicEffect", Instigator);
		World->GetTimerManager().SetTimer(PeriodHandle, Delegate, Period, true);
	}

	return bRet;
}

bool UASAbilityEffect::Stop_Implementation(AActor* Instigator)
{
	const auto * World  = GetWorld();
	if(!World) return false;
	if (World->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER)
	{
		ExecutePeriodicEffect(Instigator);
	}

	const bool bRet = Super::Stop_Implementation(Instigator);

	World->GetTimerManager().ClearTimer(DurationHandle);
	World->GetTimerManager().ClearTimer(PeriodHandle);

	auto* Comp = GetOwningComponent();
	if (!ensure(Comp))
	{
		return false;
	}

	Comp->RemoveAbility(AbilityTag);

	return bRet;
}
