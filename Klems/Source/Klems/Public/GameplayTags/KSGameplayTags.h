﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

//Input Gameplay Tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Input_Move);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Input_Look);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Input_Jump);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Input_Run);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Input_Crouch);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Input_Shoot);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Input_Reload);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Input_Punch);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Input_TabUI);

//Effects
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Effect_Reloading);



//Native abilities Gameplay Tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Run);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Shoot);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Reload);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Punch);

// Native attributes Gameplay Tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_Health);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_Infection);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_Speed);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_HitCount);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_HeadShotCount);

// Native modifiers Gameplay Tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Modifier_Infection);

//Util for know if a player is infected
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Infected);

