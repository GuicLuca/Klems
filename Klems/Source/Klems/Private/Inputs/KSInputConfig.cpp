// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs/KSInputConfig.h"
#include "GameplayTagContainer.h"
#include "EnhancedInput/Public/InputAction.h"

const UInputAction* UKSInputConfig::FindInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FKSTaggedInputAction& TaggedInputAction : TaggedInputActions)
	{
		if (TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)
		{
			return TaggedInputAction.InputAction;
		}
	}

	return nullptr;
}