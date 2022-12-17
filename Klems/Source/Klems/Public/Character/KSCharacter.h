#pragma once

#include "CoreMinimal.h"
#include "Ability/ASAbilityComponent.h"
#include "InputActionValue.h"
#include "Attribute/ASAttributeSetComponent.h"
#include "GameFramework/Character.h"
#include "KSCharacter.generated.h"

class UKSCombatComponent;
class UCameraComponent;
class UKSInputConfig;
struct FInputActionValue;

UCLASS()
class KLEMS_API AKSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AKSCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetCamera() { return Camera; }
	
	UPROPERTY(VisibleAnywhere, Category = "Ability")
	TObjectPtr<UASAbilityComponent> AbilityComponent;

	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	TObjectPtr<UASAttributeSetComponent> Attributes;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<UKSCombatComponent> CombatComponent;
	
protected:
	
	UFUNCTION()
	void OnSpeedChanged(float OldValue, float NewValue);
	
	virtual void BeginPlay() override;

	void InputMove(const FInputActionValue& InputActionValue);

	void InputLook(const FInputActionValue& InputActionValue);

	void InputJump(const FInputActionValue& InputActionValue);

	void InputCrouch(const FInputActionValue& InputActionValue);

	void InputRun(const FInputActionValue& InputActionValue);

	void InputShoot(const FInputActionValue& InputActionValue);

	void InputReload(const FInputActionValue& InputActionValue);

	void InputPunch(const FInputActionValue& InputActionValue);
	


	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> FPSMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UKSInputConfig* InputConfig;
	
};

