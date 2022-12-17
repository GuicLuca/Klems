// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ASAbilityComponent.generated.h"

class UASAbility;
/**
 * 
 */
UCLASS(ClassGroup=(Ability), meta=(BlueprintSpawnableComponent))
class ABILITYSYSTEM_API UASAbilityComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UASAbilityComponent();

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UFUNCTION(BlueprintCallable, Category="Ability")
	void AddAbility(TSubclassOf<UASAbility> AbilityClass, AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category="Ability")
	bool RemoveAbility(FGameplayTag AbilityTag);

	UFUNCTION(BlueprintCallable, Category="Ability")
	bool StartAbility(FGameplayTag AbilityTag, AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category="Ability")
	bool StopAbility(FGameplayTag AbilityTag, AActor* Instigator);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
	FGameplayTagContainer ActiveGameplayTags;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<UASAbility*> Abilities;

	UFUNCTION(Server, Reliable)
	void ServerAddAbility(TSubclassOf<UASAbility> AbilityClass, AActor* Instigator);

	UFUNCTION(Server, Reliable)
	void ServerRemoveAbility(FGameplayTag AbilityTag);

	UFUNCTION(Server, Reliable)
	void ServerStartAbility(FGameplayTag AbilityTag, AActor* Instigator);

	UFUNCTION(Server, Reliable)
	void ServerStopAbility(FGameplayTag AbilityTag, AActor* Instigator);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	TArray<TSubclassOf<UASAbility>> DefaultAbilities;
};
