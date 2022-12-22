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

	if (Duration > 0.0F)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "stop", Instigator);
		GetWorld()->GetTimerManager().SetTimer(DurationHandle, Delegate, Duration, false);
	}

	if (Period > 0.0F)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "ExecutePeriodicEffect", Instigator);
		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, Delegate, Period, true);
	}

	return bRet;
}

bool UASAbilityEffect::Stop_Implementation(AActor* Instigator)
{
	if (GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER)
	{
		ExecutePeriodicEffect(Instigator);
	}

	const bool bRet = Super::Stop_Implementation(Instigator);

	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);

	auto* Comp = GetOwningComponent();
	if (!ensure(Comp))
	{
		return false;
	}

	Comp->RemoveAbility(AbilityTag);

	return bRet;
}
