// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/ASAbilityComponent.h"
#include "Ability/ASAbility.h"
#include "Engine/ActorChannel.h"

UASAbilityComponent::UASAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UASAbilityComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool result = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for(auto* Ability : Abilities)
	{
		if(!Ability)continue;

		result |= Channel->ReplicateSubobject(Ability, *Bunch, *RepFlags);
	}
	return result;
}

void UASAbilityComponent::AddAbility(const TSubclassOf<UASAbility> AbilityClass, AActor* Instigator)
{
	if (!ensure(AbilityClass))return;
	if(!GetOwner()) return;
	if(!GetOwner()->HasAuthority())
	{
		ServerAddAbility(AbilityClass, Instigator);
		return;
	}

	auto* NewAbility = NewObject<UASAbility>(this, AbilityClass);
	if (!ensure(NewAbility))return;

	if (Abilities.Find(NewAbility) != INDEX_NONE)
	{
		Abilities.Remove(NewAbility);
	}

	Abilities.Add(NewAbility);

	if (NewAbility->bAutoStart && ensure(NewAbility->CanStart(Instigator)))
	{
		NewAbility->Start(Instigator);
	}
}

bool UASAbilityComponent::RemoveAbility(const FGameplayTag AbilityTag)
{
	if(!GetOwner()) return false;
	if(!GetOwner()->HasAuthority())
	{
		ServerRemoveAbility(AbilityTag);
		return true;
	}
	
	UASAbility* AbilityToRemove = nullptr;
	for(auto* Ability : Abilities)
	{
		if(!Ability || Ability->GetGameplayTag() != AbilityTag) continue;
		if(Ability->IsRunning()) return false;
		AbilityToRemove = Ability;
		break;
	}
	return Abilities.Remove(AbilityToRemove) != 0;
}

bool UASAbilityComponent::StartAbility(const FGameplayTag AbilityTag, AActor* Instigator)
{
	if(!GetOwner()) return false;
	if(!GetOwner()->HasAuthority())
	{
		ServerStartAbility(AbilityTag, Instigator);
		return true;
	}
	
	for(auto* Ability : Abilities)
	{
		if(!Ability || Ability->GetGameplayTag() != AbilityTag) continue;
		if(!Ability->CanStart(Instigator) || Ability->IsRunning()) return false; // remove the second condition to start sevrel times an ability
		Ability->Start(Instigator);
		return true;
	}
	return false;
}

bool UASAbilityComponent::StopAbility(const FGameplayTag AbilityTag, AActor* Instigator)
{
	if(!GetOwner()) return false;
	if(!GetOwner()->HasAuthority())
	{
		ServerStopAbility(AbilityTag, Instigator);
		return true;
	}
	
	for(auto* Ability : Abilities)
	{
		if(!Ability || Ability->GetGameplayTag() != AbilityTag) continue;
		if(!Ability->CanStop(Instigator) || !Ability->IsRunning()) return false; // remove the second condition to start sevrel times an ability
		Ability->Stop(Instigator);
		return true;
	}
	return false;
}

void UASAbilityComponent::BeginPlay()
{
	
	Super::BeginPlay();
	if(!GetOwner()) return;
	if(!GetOwner()->HasAuthority()) return;;
	
	for (const auto Ability : DefaultAbilities)
	{
		AddAbility(Ability, GetOwner());
	}
}

void UASAbilityComponent::ServerAddAbility_Implementation(TSubclassOf<UASAbility> AbilityClass, AActor* Instigator)
{
	AddAbility(AbilityClass, Instigator);
}

void UASAbilityComponent::ServerRemoveAbility_Implementation(FGameplayTag AbilityTag)
{
	RemoveAbility(AbilityTag);
}

void UASAbilityComponent::ServerStartAbility_Implementation(FGameplayTag AbilityTag, AActor* Instigator)
{
	StartAbility(AbilityTag, Instigator);
}

void UASAbilityComponent::ServerStopAbility_Implementation(FGameplayTag AbilityTag, AActor* Instigator)
{
	StopAbility(AbilityTag, Instigator);
}
