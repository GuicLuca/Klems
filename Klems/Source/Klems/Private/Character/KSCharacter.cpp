// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/KSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Combat/KSCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTags/KSGameplayTags.h"
#include "Infection/KSInfectionTile.h"
#include "Inputs/KSTaggedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AKSCharacter::AKSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	// Position the camera slightly above the eyes.
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// Enable the pawn to control camera rotation.
	Camera->bUsePawnControlRotation = true;
	
	AbilityComponent = CreateDefaultSubobject<UASAbilityComponent>(TEXT("AbilityComponent"));

	Attributes = CreateDefaultSubobject<UASAttributeSetComponent>(TEXT("AttributeComponent"));

	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	CombatComponent = CreateDefaultSubobject<UKSCombatComponent>(TEXT("Combat Component"));
	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);

	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(Camera);

	// Disable some environmental shadows to preserve the illusion of having a single mesh.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//Disable the third person on non owner-pawns
	GetMesh()->bOwnerNoSee = true;
}

void AKSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AKSCharacter,InfectionDensity);
	DOREPLIFETIME(AKSCharacter,Health);
	DOREPLIFETIME(AKSCharacter,Camera);
}

void AKSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(!HasAuthority()) return;;
	
	checkf(Attributes, TEXT("Character component ill formed ! BP corruption?"));
	
	auto* SpeedAttribute = Attributes->GetAttribute(TAG_Attribute_Speed);
	if(!ensureAlwaysMsgf(SpeedAttribute, TEXT("No speed attribute, your character is ill formated !"))) return;

	SpeedAttribute->CurrentValueChanged.AddDynamic(this, &AKSCharacter::OnSpeedChanged);
	
	auto* HealthAttribute = Attributes->GetAttribute(TAG_Attribute_Health);
	if(!ensureAlwaysMsgf(HealthAttribute, TEXT("No health attribute, your character is ill formated !"))) return;

	HealthAttribute->CurrentValueChanged.AddDynamic(this, &AKSCharacter::OnHealthChanged);
	
	auto* InfectAttribute = Attributes->GetAttribute(TAG_Attribute_Infection);
	if(!ensureAlwaysMsgf(InfectAttribute, TEXT("No infect attribute, your character is ill formated !"))) return;

	InfectAttribute->CurrentValueChanged.AddDynamic(this, &AKSCharacter::OnInfectChanged);
	
	startInfection();
	
}

/***************************NATIVE EVENTS*****************************/

void AKSCharacter::TakeHit_Implementation()
{
}

void AKSCharacter::Reload_Implementation()
{
}

void AKSCharacter::Shoot_Implementation()
{
}

void AKSCharacter::Die_Implementation()
{
}

void AKSCharacter::StartRun_Implementation()
{
}

void AKSCharacter::StopRun_Implementation()
{
}

/**********************************************************************/


/****************************INFECTION*********************************/

void AKSCharacter::SetInfectedMode()
{
	if(InfectionDensity >=1)
	{
		bIsInfected = true;
		
		for(auto tag : AbilitiesRemovedByInfection)
		{
			AbilityComponent->RemoveAbility(tag);
		}

		for(auto ability : AbilitiesGrantedByInfection)
		{
			AbilityComponent->AddAbility(ability, this);
		}

		stopInfection();
	}
}

void AKSCharacter::addInfection()
{
	if(!HasAuthority()) return;
	TArray<AActor*> OverlappedActors;
	GetCapsuleComponent()->GetOverlappingActors(OverlappedActors);

	for(auto* Actor : OverlappedActors)
	{
		auto tile = Cast<AKSInfectionTile>(Actor);
		if(tile)
		{
			const float infectionDensity = tile->InfectionDensity;
			auto* attribute = Attributes->GetAttribute(TAG_Attribute_Infection);
			attribute->SetCurrentValue(attribute->GetCurrentValue()+infectionDensity);
			//this->InfectionDensity += infectionDensity;
			//SetInfectedMode();
			break;
		}
	}
}

void AKSCharacter::startInfection_Implementation()
{
	if(!HasAuthority()) return;
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AKSCharacter::addInfection, 1.0f, true);
}

void AKSCharacter::stopInfection_Implementation()
{
	GetWorldTimerManager().ClearTimer(MemberTimerHandle);
	CombatComponent->MaxAmmo = 1;
	CombatComponent->Ammo = 1;
}

//called by attributes (server)
void AKSCharacter::OnInfectChanged(float OldValue, float NewValue)
{
	if(!HasAuthority()) return;
	UE_LOG(LogTemp,Verbose, TEXT("HEALTH delagate called"));
	InfectionDensity = NewValue;
	SetInfectedMode();
}

//called by client
void AKSCharacter::OnRep_InfectionDensityChanged()
{
	SetInfectedMode();
}

/**********************************************************************/

/*******************************AMMO***********************************/

//called by client
void AKSCharacter::OnAmmoChanged_Implementation(int32 OldValue, int32 NewValue)
{

}

/**********************************************************************/

//called by attribute (server)
void AKSCharacter::OnSpeedChanged(float OldValue, float NewValue)
{
	if(!HasAuthority()) return;
	UE_LOG(LogTemp,Verbose, TEXT("SPEED delagate called"));
	auto* Mouvement = GetCharacterMovement();
	if(!ensureAlwaysMsgf(Mouvement, TEXT("No mouvement component. Character ill formed!"))) return;
	Mouvement->MaxWalkSpeed = NewValue;
}

/*****************************************HEALTH*******************************************/

//called by attribute (server)
void AKSCharacter::OnHealthChanged(float OldValue, float NewValue)
{
	if(!HasAuthority()) return;
	UE_LOG(LogTemp,Verbose, TEXT("HEALTH delagate called"));
	Health= NewValue;
	if(Health <= 0)
		Die();
}

/*
//called by server
void AKSCharacter::DecrementHealth_Implementation(float amount)
{
	Health -= amount;
	if(Health <= 0)
		Die();
}
*/

//called by client
void AKSCharacter::OnRep_HealthChanged()
{
	TakeHit();
	if(Health <= 0)
		Die();
}

/******************************************************************************************/

/*****************************************INPUTS*******************************************/

void AKSCharacter::InputMove(const FInputActionValue& InputActionValue)
{
	const auto MoveVector = InputActionValue.Get<FVector2d>();

	if(Controller == nullptr || MoveVector.SquaredLength() == 0) return;

	//Get the forward direction from the controller
	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
	const FVector RightDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
	AddMovementInput(ForwardDirection, MoveVector.Y);
	AddMovementInput(RightDirection, -MoveVector.X);
}

void AKSCharacter::InputLook(const FInputActionValue& InputActionValue)
{
	const auto LookVector = InputActionValue.Get<FVector2d>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(-LookVector.Y);	
}

void AKSCharacter::InputJump(const FInputActionValue& InputActionValue)
{
	Jump();
}

void AKSCharacter::InputCrouch(const FInputActionValue& InputActionValue)
{
	if(InputActionValue.Get<bool>())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AKSCharacter::InputRun(const FInputActionValue& InputActionValue)
{
	if(InputActionValue.Get<bool>())
	{
		StartRun();
		AbilityComponent->StartAbility(TAG_Ability_Run,this);
	}
	else
	{
		StopRun();
		AbilityComponent->StopAbility(TAG_Ability_Run,this);
	}
}

void AKSCharacter::InputShoot(const FInputActionValue& InputActionValue)
{
	if(InputActionValue.Get<bool>())
	{
		if(CombatComponent->Ammo > 0 && GetVelocity().Length() < 850)
			Shoot();
		AbilityComponent->StartAbility(TAG_Ability_Shoot,this);
		AbilityComponent->StartAbility(TAG_Ability_Punch,this);
	
	}
	else
	{
		/*
		AbilityComponent->StopAbility(TAG_Ability_Shoot,this);
		AbilityComponent->StopAbility(TAG_Ability_Punch,this);
		*/
	}
	
	
}

void AKSCharacter::InputReload(const FInputActionValue& InputActionValue)
{
	if(InputActionValue.Get<bool>())
	{
		if(GetVelocity().Length() < 850)
			Reload();
		AbilityComponent->StartAbility(TAG_Ability_Reload,this);
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([&]()
		{
			AbilityComponent->StopAbility(TAG_Ability_Reload,this);
		});
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,TimerDelegate,3,false);
		
	}
	else
	{
		
	}
}

void AKSCharacter::InputPunch(const FInputActionValue& InputActionValue)
{
	if(InputActionValue.Get<bool>())
	{
		AbilityComponent->StartAbility(TAG_Ability_Punch,this);
	}
	else
	{
		AbilityComponent->StopAbility(TAG_Ability_Punch,this);
	}
}




void AKSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* TaggedInputComponent = Cast<UKSTaggedInputComponent>(PlayerInputComponent);
	check(TaggedInputComponent);

	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Move, ETriggerEvent::Triggered, this, &AKSCharacter::InputMove);
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Look, ETriggerEvent::Triggered, this, &AKSCharacter::InputLook);
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Jump, ETriggerEvent::Triggered, this, &AKSCharacter::InputJump);
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Crouch, ETriggerEvent::Triggered, this, &AKSCharacter::InputCrouch);
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Run, ETriggerEvent::Triggered, this, &AKSCharacter::InputRun);
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Shoot, ETriggerEvent::Triggered, this, &AKSCharacter::InputShoot);
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Reload, ETriggerEvent::Triggered, this, &AKSCharacter::InputReload);
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Punch, ETriggerEvent::Triggered, this, &AKSCharacter::InputPunch);
	//TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_TabUI, ETriggerEvent::Triggered, this, &AKSCharacter::InputTab);
}

/******************************************************************************************/