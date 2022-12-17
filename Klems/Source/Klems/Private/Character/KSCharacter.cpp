// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/KSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Combat/KSCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTags/KSGameplayTags.h"
#include "Inputs/KSTaggedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AKSCharacter::AKSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;
	bUseControllerRotationPitch = true;

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
}

void AKSCharacter::SetInfectedMode()
{
	ServerSetInfectedMode();
}

void AKSCharacter::startInfection()
{
	GetWorldTimerManager().SetTimer()
}

void AKSCharacter::stopInfection()
{
}

void AKSCharacter::OnInfectChanged(float OldValue, float NewValue)
{
	SetInfectedMode();
}

void AKSCharacter::ServerSetInfectedMode_Implementation()
{
	auto const InfectionAttribute = Attributes->GetAttribute(TAG_Attribute_Infection);
	if(InfectionAttribute->GetCurrentValue() >=1)
	{
		for(auto const tag : AbilitiesRemovedByInfection)
		{
			AbilityComponent->RemoveAbility(tag);
		}

		for(auto const ability : AbilitiesGrantedByInfection)
		{
			AbilityComponent->AddAbility(ability, this);
		}
		
	}
}

void AKSCharacter::OnSpeedChanged(float OldValue, float NewValue)
{
	UE_LOG(LogTemp,Verbose, TEXT("SPEED delagate called"));
	auto* Mouvement = GetCharacterMovement();
	if(!ensureAlwaysMsgf(Mouvement, TEXT("No mouvement component. Character ill formed!"))) return;
	Mouvement->MaxWalkSpeed = NewValue;
}

void AKSCharacter::BeginPlay()
{
	Super::BeginPlay();

	checkf(Attributes, TEXT("Character component ill formed ! BP corruption?"));

	auto* SpeedAttribute = Attributes->GetAttribute(TAG_Attribute_Speed);
	if(!ensureAlwaysMsgf(SpeedAttribute, TEXT("No speed attribute, your character is ill formated !"))) return;

	SpeedAttribute->CurrentValueChanged.AddDynamic(this, &AKSCharacter::OnSpeedChanged);

	auto* InfectAttribute = Attributes->GetAttribute(TAG_Attribute_Infection);
	if(!ensureAlwaysMsgf(InfectAttribute, TEXT("No infect attribute, your character is ill formated !"))) return;

	InfectAttribute->CurrentValueChanged.AddDynamic(this, &AKSCharacter::OnSpeedChanged);
	
	
}

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
		AbilityComponent->StartAbility(TAG_Ability_Run,this);
	}
	else
	{
		AbilityComponent->StopAbility(TAG_Ability_Run,this);
	}
}

void AKSCharacter::InputShoot(const FInputActionValue& InputActionValue)
{
	if(InputActionValue.Get<bool>())
	{
		AbilityComponent->StartAbility(TAG_Ability_Shoot,this);
	}
	else
	{
		AbilityComponent->StopAbility(TAG_Ability_Shoot,this);
	}
}

void AKSCharacter::InputReload(const FInputActionValue& InputActionValue)
{
	if(InputActionValue.Get<bool>())
	{
		AbilityComponent->StartAbility(TAG_Ability_Reload,this);
	}
	else
	{
		AbilityComponent->StopAbility(TAG_Ability_Reload,this);
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
}
