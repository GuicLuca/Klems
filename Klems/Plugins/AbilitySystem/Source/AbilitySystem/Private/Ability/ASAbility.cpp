// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/ASAbility.h"

bool UASAbility::CanStart_Implementation(AActor* Instigator)
{
	if (bRunning)
	{
		return false;
	}

	const auto* Comp = GetOwningComponent();
	if (!ensure(Comp))
	{
		return nullptr;
	}

	const bool bBlocked = Comp->ActiveGameplayTags.HasAny(BlockedTags);
	UE_LOG(LogTemp, Log, TEXT("Can Start %s :%d"), *GetNameSafe(this), bBlocked);
	return !bBlocked;
}

bool UASAbility::Start_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running : %s"), *GetNameSafe(this));
	auto* Comp = GetOwningComponent();
	if (!ensure(Comp))
	{
		return false;
	}

	Comp->ActiveGameplayTags.AppendTags(GrantedTags);
	bRunning = true;
	return true;
}

bool UASAbility::CanStop_Implementation(AActor* Instigator)
{
	return true;
}

bool UASAbility::Stop_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped : %s"), *GetNameSafe(this));
	ensureAlways(bRunning);

	auto* Comp = GetOwningComponent();
	if (!ensure(Comp))
	{
		return false;
	}

	Comp->ActiveGameplayTags.RemoveTags(GrantedTags);
	bRunning = false;
	return true;
}

FGameplayTagContainer UASAbility::IsBlockedBy(AActor* Instigator)
{
	if (CanStart(Instigator))
	{
		return FGameplayTagContainer{};
	}
	const auto* Comp = GetOwningComponent();
	if (!ensure(Comp))
	{
		return FGameplayTagContainer{};
	}

	return Comp->ActiveGameplayTags.Filter(BlockedTags);
}

UWorld* UASAbility::GetWorld() const
{
	const auto* Comp = GetOwningComponent();
	if (!Comp)
	{
		return nullptr;
	}

	return Comp->GetWorld();
}

UASAbilityComponent* UASAbility::GetOwningComponent() const
{
	return Cast<UASAbilityComponent>(GetOuter());
}
